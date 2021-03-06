/* Cabal - Legacy Game Implementations
 *
 * Cabal is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

// Based on the ScummVM (GPLv2+) file of the same name

#include "audio/decoders/aac.h"

#ifdef USE_FAAD

#include "common/debug.h"
#include "common/memstream.h"
#include "common/stream.h"
#include "common/textconsole.h"
#include "common/util.h"

#include "audio/audiostream.h"
#include "audio/decoders/codec.h"
#include "audio/decoders/pcm.h"

#include <neaacdec.h>

namespace Audio {

class AACDecoder : public Codec, public PacketizedAudioStream {
public:
	AACDecoder(Common::SeekableReadStream &extraData);
	~AACDecoder();

	// AudioStream API
	uint getChannels() const { return _channels; }
	int getRate() const { return _rate; }
	bool endOfData() const { return _audStream->endOfData(); }
	bool endOfStream() const { return _audStream->endOfStream(); }
	int readBuffer(int16 *buffer, const int numSamples) { return _audStream->readBuffer(buffer, numSamples); }

	// PacketizedAudioStream API
	void finish() { _audStream->finish(); }
	void queuePacket(Common::SeekableReadStream *data);

	// Codec API
	AudioStream *decodeFrame(Common::SeekableReadStream &stream);

private:
	NeAACDecHandle _handle;
	byte _channels;
	unsigned long _rate;

	// Backing stream for the PacketizedAudioStream
	Common::ScopedPtr<QueuingAudioStream> _audStream;
};

AACDecoder::AACDecoder(Common::SeekableReadStream &extraData) {
	// Open the library
	_handle = NeAACDecOpen();

	// Configure the library to our needs
	NeAACDecConfigurationPtr conf = NeAACDecGetCurrentConfiguration(_handle);
	conf->outputFormat = FAAD_FMT_16BIT; // We only support 16bit audio
	conf->downMatrix = 1;                // Convert from 5.1 to stereo if required
	NeAACDecSetConfiguration(_handle, conf);

	// Copy the extra data to a buffer
	extraData.seek(0);
	Common::ScopedArray<byte> extraDataBuf(new byte[extraData.size()]);
	extraData.read(extraDataBuf.get(), extraData.size());

	// Initialize with our extra data
	// NOTE: This code assumes the extra data is coming from an MPEG-4 file!
	int err = NeAACDecInit2(_handle, extraDataBuf.get(), extraData.size(), &_rate, &_channels);
	if (err < 0)
		error("Could not initialize AAC decoder: %s", NeAACDecGetErrorMessage(err));

	_audStream.reset(makeQueuingAudioStream(_rate, _channels));
}

AACDecoder::~AACDecoder() {
	NeAACDecClose(_handle);
}

AudioStream *AACDecoder::decodeFrame(Common::SeekableReadStream &stream) {
	// read everything into a buffer
	uint32 inBufferPos = 0;
	uint32 inBufferSize = stream.size();
	Common::ScopedArray<byte> inBuffer(new byte[inBufferSize]);
	stream.read(inBuffer.get(), inBufferSize);

	QueuingAudioStream *audioStream = makeQueuingAudioStream(_rate, _channels);

	// Decode until we have enough samples (or there's no more left)
	while (inBufferPos < inBufferSize) {
		NeAACDecFrameInfo frameInfo;
		void *decodedSamples = NeAACDecDecode(_handle, &frameInfo, inBuffer.get() + inBufferPos, inBufferSize - inBufferPos);

		if (frameInfo.error != 0)
			error("Failed to decode AAC frame: %s", NeAACDecGetErrorMessage(frameInfo.error));

		byte *buffer = (byte *)malloc(frameInfo.samples * 2);
		memcpy(buffer, decodedSamples, frameInfo.samples * 2);

		byte flags = FLAG_16BITS | FLAG_NATIVE_ENDIAN;

		if (_channels == 2)
			flags |= FLAG_STEREO;

		audioStream->queueBuffer(buffer, frameInfo.samples * 2, DisposeAfterUse::YES, flags);

		inBufferPos += frameInfo.bytesconsumed;
	}

	audioStream->finish();
	return audioStream;
}

void AACDecoder::queuePacket(Common::SeekableReadStream *data) {
	_audStream->queueAudioStream(decodeFrame(*data));
	delete data;
}

Codec *makeAACDecoder(Common::SeekableReadStream &extraData) {
	return new AACDecoder(extraData);
}

PacketizedAudioStream *makeAACStream(Common::SeekableReadStream &extraData) {
	return new AACDecoder(extraData);
}

} // End of namespace Audio

#endif // #ifdef USE_FAAD
