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

#include "common/debug.h"
#include "common/file.h"
#include "common/mutex.h"
#include "common/textconsole.h"
#include "common/queue.h"
#include "common/util.h"

#include "audio/audiostream.h"
#include "audio/decoders/flac.h"
#include "audio/decoders/mp3.h"
#include "audio/decoders/quicktime.h"
#include "audio/decoders/pcm.h"
#include "audio/decoders/vorbis.h"
#include "audio/mixer.h"


namespace Audio {

struct StreamFileFormat {
	/** Decodername */
	const char *decoderName;
	const char *fileExtension;
	/**
	 * Pointer to a function which tries to open a file of type StreamFormat.
	 * Return NULL in case of an error (invalid/nonexisting file).
	 */
	SeekableAudioStream *(*openStreamFile)(Common::SeekableReadStream *stream, DisposeAfterUse::Flag disposeAfterUse);
};

static const StreamFileFormat STREAM_FILEFORMATS[] = {
	/* decoderName,  fileExt, openStreamFunction */
#ifdef USE_FLAC
	{ "FLAC",         ".flac", makeFLACStream },
	{ "FLAC",         ".fla",  makeFLACStream },
#endif
#ifdef USE_VORBIS
	{ "Ogg Vorbis",   ".ogg",  makeVorbisStream },
#endif
#ifdef USE_MAD
	{ "MPEG Layer 3", ".mp3",  makeMP3Stream },
#endif
	{ "MPEG-4 Audio",   ".m4a",  makeQuickTimeStream },
};

SeekableAudioStream *SeekableAudioStream::openStreamFile(const Common::String &basename) {
	SeekableAudioStream *stream = NULL;
	Common::File *fileHandle = new Common::File();

	for (int i = 0; i < ARRAYSIZE(STREAM_FILEFORMATS); ++i) {
		Common::String filename = basename + STREAM_FILEFORMATS[i].fileExtension;
		fileHandle->open(filename);
		if (fileHandle->isOpen()) {
			// Create the stream object
			stream = STREAM_FILEFORMATS[i].openStreamFile(fileHandle, DisposeAfterUse::YES);
			fileHandle = 0;
			break;
		}
	}

	delete fileHandle;

	if (stream == NULL)
		debug(1, "SeekableAudioStream::openStreamFile: Could not open compressed AudioFile %s", basename.c_str());

	return stream;
}

#pragma mark -
#pragma mark --- LoopingAudioStream ---
#pragma mark -

LoopingAudioStream::LoopingAudioStream(RewindableAudioStream *stream, uint loops, DisposeAfterUse::Flag disposeAfterUse)
    : _parent(stream, disposeAfterUse), _loops(loops), _completeIterations(0) {
	assert(stream);

	if (!stream->rewind()) {
		// TODO: Properly indicate error
		_loops = _completeIterations = 1;
	}
	if (stream->endOfStream()) {
		// Apparently this is an empty stream
		_loops = _completeIterations = 1;
	}
}

int LoopingAudioStream::readBuffer(int16 *buffer, const int numSamples) {
	if ((_loops && _completeIterations == _loops) || !numSamples)
		return 0;

	int samplesRead = _parent->readBuffer(buffer, numSamples);

	if (_parent->endOfStream()) {
		++_completeIterations;
		if (_completeIterations == _loops)
			return samplesRead;

		const int remainingSamples = numSamples - samplesRead;

		if (!_parent->rewind()) {
			// TODO: Properly indicate error
			_loops = _completeIterations = 1;
			return samplesRead;
		}
		if (_parent->endOfStream()) {
			// Apparently this is an empty stream
			_loops = _completeIterations = 1;
		}

		return samplesRead + readBuffer(buffer + samplesRead, remainingSamples);
	}

	return samplesRead;
}

bool LoopingAudioStream::endOfData() const {
	return (_loops != 0 && _completeIterations == _loops) || _parent->endOfData();
}

bool LoopingAudioStream::endOfStream() const {
	return _loops != 0 && _completeIterations == _loops;
}

AudioStream *makeLoopingAudioStream(RewindableAudioStream *stream, uint loops) {
	if (loops != 1)
		return new LoopingAudioStream(stream, loops);
	else
		return stream;
}

AudioStream *makeLoopingAudioStream(SeekableAudioStream *stream, Common::Timestamp start, Common::Timestamp end, uint loops) {
	if (!start.totalNumberOfFrames() && (!end.totalNumberOfFrames() || end == stream->getLength())) {
		return makeLoopingAudioStream(stream, loops);
	} else {
		if (!end.totalNumberOfFrames())
			end = stream->getLength();

		if (start >= end) {
			warning("makeLoopingAudioStream: start (%d) >= end (%d)", start.msecs(), end.msecs());
			delete stream;
			return 0;
		}

		return makeLoopingAudioStream(new SubSeekableAudioStream(stream, start, end), loops);
	}
}

#pragma mark -
#pragma mark --- SubLoopingAudioStream ---
#pragma mark -

SubLoopingAudioStream::SubLoopingAudioStream(SeekableAudioStream *stream,
                                             uint loops,
                                             const Common::Timestamp loopStart,
                                             const Common::Timestamp loopEnd,
                                             DisposeAfterUse::Flag disposeAfterUse)
    : _parent(stream, disposeAfterUse), _loops(loops),
      _pos(0, getRate() * getChannels()),
      _loopStart(convertTimeToStreamPos(loopStart, getRate(), getChannels())),
      _loopEnd(convertTimeToStreamPos(loopEnd, getRate(), getChannels())),
      _done(false) {
	assert(loopStart < loopEnd);

	if (!_parent->rewind())
		_done = true;
}

int SubLoopingAudioStream::readBuffer(int16 *buffer, const int numSamples) {
	if (_done)
		return 0;

	int framesLeft = MIN(_loopEnd.frameDiff(_pos), numSamples);
	int framesRead = _parent->readBuffer(buffer, framesLeft);
	_pos = _pos.addFrames(framesRead);

	if (framesRead < framesLeft && _parent->endOfStream()) {
		// TODO: Proper error indication.
		_done = true;
		return framesRead;
	} else if (_pos == _loopEnd) {
		if (_loops != 0) {
			--_loops;
			if (!_loops) {
				_done = true;
				return framesRead;
			}
		}

		if (!_parent->seek(_loopStart)) {
			// TODO: Proper error indication.
			_done = true;
			return framesRead;
		}

		_pos = _loopStart;
		framesLeft = numSamples - framesLeft;
		return framesRead + readBuffer(buffer + framesRead, framesLeft);
	} else {
		return framesRead;
	}
}

bool SubLoopingAudioStream::endOfData() const {
	// We're out of data if this stream is finished or the parent
	// has run out of data for now.
	return _done || _parent->endOfData();
}

bool SubLoopingAudioStream::endOfStream() const {
	// The end of the stream has been reached only when we've gone
	// through all the iterations.
	return _done;
}

#pragma mark -
#pragma mark --- SubSeekableAudioStream ---
#pragma mark -

SubSeekableAudioStream::SubSeekableAudioStream(SeekableAudioStream *parent, const Common::Timestamp start, const Common::Timestamp end, DisposeAfterUse::Flag disposeAfterUse)
    : _parent(parent, disposeAfterUse),
      _start(convertTimeToStreamPos(start, getRate(), getChannels())),
      _pos(0, getRate() * getChannels()),
      _length(convertTimeToStreamPos(end, getRate(), getChannels()) - _start) {

	assert(_length.totalNumberOfFrames() % getChannels() == 0);
	_parent->seek(_start);
}

int SubSeekableAudioStream::readBuffer(int16 *buffer, const int numSamples) {
	int framesLeft = MIN(_length.frameDiff(_pos), numSamples);
	int framesRead = _parent->readBuffer(buffer, framesLeft);
	_pos = _pos.addFrames(framesRead);
	return framesRead;
}

bool SubSeekableAudioStream::seek(const Common::Timestamp &where) {
	_pos = convertTimeToStreamPos(where, getRate(), getChannels());
	if (_pos > _length) {
		_pos = _length;
		return false;
	}

	if (_parent->seek(_pos + _start)) {
		return true;
	} else {
		_pos = _length;
		return false;
	}
}

#pragma mark -
#pragma mark --- Queueing audio stream ---
#pragma mark -


void QueuingAudioStream::queueBuffer(byte *data, uint32 size, DisposeAfterUse::Flag disposeAfterUse, byte flags) {
	AudioStream *stream = makePCMStream(data, size, getRate(), flags, disposeAfterUse);
	queueAudioStream(stream, DisposeAfterUse::YES);
}


class QueuingAudioStreamImpl : public QueuingAudioStream {
private:
	/**
	 * We queue a number of (pointers to) audio stream objects.
	 * In addition, we need to remember for each stream whether
	 * to dispose it after all data has been read from it.
	 * Hence, we don't store pointers to stream objects directly,
	 * but rather StreamHolder structs.
	 */
	struct StreamHolder {
		AudioStream *_stream;
		DisposeAfterUse::Flag _disposeAfterUse;
		StreamHolder(AudioStream *stream, DisposeAfterUse::Flag disposeAfterUse)
		    : _stream(stream),
		      _disposeAfterUse(disposeAfterUse) {}
	};

	/**
	 * The sampling rate of this audio stream.
	 */
	const int _rate;

	/**
	 * How many channels this audio stream contains.
	 */
	const uint _channels;

	/**
	 * This flag is set by the finish() method only. See there for more details.
	 */
	bool _finished;

	/**
	 * A mutex to avoid access problems (causing e.g. corruption of
	 * the linked list) in thread aware environments.
	 */
	Common::Mutex _mutex;

	/**
	 * The queue of audio streams.
	 */
	Common::Queue<StreamHolder> _queue;

public:
	QueuingAudioStreamImpl(int rate, uint channels)
	    : _rate(rate), _channels(channels), _finished(false) {}
	~QueuingAudioStreamImpl();

	// Implement the AudioStream API
	virtual int readBuffer(int16 *buffer, const int numSamples);
	virtual uint getChannels() const { return _channels; }
	virtual int getRate() const { return _rate; }

	virtual bool endOfData() const {
		Common::StackLock lock(_mutex);
		return _queue.empty() || _queue.front()._stream->endOfData();
	}

	virtual bool endOfStream() const {
		Common::StackLock lock(_mutex);
		return _finished && _queue.empty();
	}

	// Implement the QueuingAudioStream API
	virtual void queueAudioStream(AudioStream *stream, DisposeAfterUse::Flag disposeAfterUse);

	virtual void finish() {
		Common::StackLock lock(_mutex);
		_finished = true;
	}

	uint32 numQueuedStreams() const {
		Common::StackLock lock(_mutex);
		return _queue.size();
	}
};

QueuingAudioStreamImpl::~QueuingAudioStreamImpl() {
	while (!_queue.empty()) {
		StreamHolder tmp = _queue.pop();
		if (tmp._disposeAfterUse == DisposeAfterUse::YES)
			delete tmp._stream;
	}
}

void QueuingAudioStreamImpl::queueAudioStream(AudioStream *stream, DisposeAfterUse::Flag disposeAfterUse) {
	assert(!_finished);
	if ((stream->getRate() != getRate()) || (stream->getChannels() != getChannels()))
		error("QueuingAudioStreamImpl::queueAudioStream: stream has mismatched parameters");

	Common::StackLock lock(_mutex);
	_queue.push(StreamHolder(stream, disposeAfterUse));
}

int QueuingAudioStreamImpl::readBuffer(int16 *buffer, const int numSamples) {
	Common::StackLock lock(_mutex);
	int samplesDecoded = 0;

	while (samplesDecoded < numSamples && !_queue.empty()) {
		AudioStream *stream = _queue.front()._stream;
		samplesDecoded += stream->readBuffer(buffer + samplesDecoded, numSamples - samplesDecoded);

		// Done with the stream completely
		if (stream->endOfStream()) {
			StreamHolder tmp = _queue.pop();
			if (tmp._disposeAfterUse == DisposeAfterUse::YES)
				delete stream;
			continue;
		}

		// Done with data but not the stream, bail out
		if (stream->endOfData())
			break;
	}

	return samplesDecoded;
}

QueuingAudioStream *makeQueuingAudioStream(int rate, uint channels) {
	return new QueuingAudioStreamImpl(rate, channels);
}

Common::Timestamp convertTimeToStreamPos(const Common::Timestamp &where, int rate, uint channels) {
	Common::Timestamp result(where.convertToFramerate(rate * channels));

	// When the Stream is a multichannel stream, we have to assure
	// that the sample position is a channel-divisible number.
	if (channels > 1) {
		int remainder = result.totalNumberOfFrames() % channels;

		if (remainder > 0)
			result = result.addFrames(-remainder);
	}

	// Since Timestamp allows sub-frame-precision it might lead to odd behaviors
	// when we would just return result.
	//
	// An example is when converting the timestamp 500ms to a 11025 Hz based
	// stream. It would have an internal frame counter of 5512.5. Now when
	// doing calculations at frame precision, this might lead to unexpected
	// results: The frame difference between a timestamp 1000ms and the above
	// mentioned timestamp (both with 11025 as framerate) would be 5512,
	// instead of 5513, which is what a frame-precision based code would expect.
	//
	// By creating a new Timestamp with the given parameters, we create a
	// Timestamp with frame-precision, which just drops a sub-frame-precision
	// information (i.e. rounds down).
	return Common::Timestamp(result.secs(), result.numberOfFrames(), result.framerate());
}

/**
 * An AudioStream wrapper that cuts off the amount of samples read after a
 * given time length is reached.
 */
class LimitingAudioStream : public AudioStream {
public:
	LimitingAudioStream(AudioStream *parentStream, const Common::Timestamp &length, DisposeAfterUse::Flag disposeAfterUse) :
			_parentStream(parentStream), _samplesRead(0), _disposeAfterUse(disposeAfterUse),
			_totalSamples(length.convertToFramerate(getRate()).totalNumberOfFrames() * getChannels()) {}

	~LimitingAudioStream() {
		if (_disposeAfterUse == DisposeAfterUse::YES)
			delete _parentStream;
	}

	int readBuffer(int16 *buffer, const int numSamples) {
		// Cap us off so we don't read past _totalSamples
		int samplesRead = _parentStream->readBuffer(buffer, MIN<int>(numSamples, _totalSamples - _samplesRead));
		_samplesRead += samplesRead;
		return samplesRead;
	}

	bool endOfData() const { return _parentStream->endOfData() || reachedLimit(); }
	bool endOfStream() const { return _parentStream->endOfStream() || reachedLimit(); }
	uint getChannels() const { return _parentStream->getChannels(); }
	int getRate() const { return _parentStream->getRate(); }

private:
	bool reachedLimit() const { return _samplesRead >= _totalSamples; }

	AudioStream *_parentStream;
	DisposeAfterUse::Flag _disposeAfterUse;
	uint32 _totalSamples, _samplesRead;
};

AudioStream *makeLimitingAudioStream(AudioStream *parentStream, const Common::Timestamp &length, DisposeAfterUse::Flag disposeAfterUse) {
	return new LimitingAudioStream(parentStream, length, disposeAfterUse);
}

/**
 * An AudioStream that plays nothing and immediately returns that
 * the endOfStream() has been reached
 */
class NullAudioStream : public AudioStream {
public:
	uint getChannels() const { return 1; }
	int getRate() const;
	int readBuffer(int16 *data, const int numSamples) { return 0; }
	bool endOfData() const { return true; }
};

int NullAudioStream::getRate() const {
	return g_system->getMixer()->getOutputRate();
}

AudioStream *makeNullAudioStream() {
	return new NullAudioStream();
}

class ReversedStereoAudioStream : public AudioStream {
public:
	ReversedStereoAudioStream(AudioStream *parentStream, DisposeAfterUse::Flag disposeAfterUse) : _parentStream(parentStream, disposeAfterUse) {}

	int readBuffer(int16 *buffer, const int numSamples);
	uint getChannels() const { return 2; }
	bool endOfData() const { return _parentStream->endOfData(); }
	bool endOfStream() const { return _parentStream->endOfStream(); }
	int getRate() const { return _parentStream->getRate(); }

private:
	Common::DisposablePtr<AudioStream> _parentStream;
};

int ReversedStereoAudioStream::readBuffer(int16 *buffer, const int numSamples) {
	int samples = _parentStream->readBuffer(buffer, numSamples);

	for (int i = 0; i < samples * 2; i += 2)
		SWAP(buffer[i], buffer[i + 1]);

	return samples;
}

AudioStream *makeReversedStereoAudioStream(AudioStream *parentStream, DisposeAfterUse::Flag disposeAfterUse) {
	if (!parentStream || parentStream->getChannels() != 2)
		return parentStream;

	return new ReversedStereoAudioStream(parentStream, disposeAfterUse);
}

} // End of namespace Audio
