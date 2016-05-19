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

/**
 * @file
 * Sound decoder used in engines:
 *  - groovie
 */

#ifndef AUDIO_AAC_H
#define AUDIO_AAC_H

#include "common/scummsys.h"

#ifdef USE_FAAD

namespace Common {
class SeekableReadStream;
}

namespace Audio {

class Codec;
class PacketizedAudioStream;

/**
 * Create a new Codec for decoding AAC data of an MPEG-4 file in the given stream.
 *
 * @note This should *only* be called by our QuickTime/MPEG-4 decoder since it relies
 *       on the MPEG-4 extra data. If you want to decode a file using AAC, go use
 *       makeQuickTimeStream() instead!
 * @param extraData         the SeekableReadStream from which to read the AAC extra data
 * @return  a new Codec, or NULL, if an error occurred
 */
Codec *makeAACDecoder(Common::SeekableReadStream &extraData);

/**
 * Create a PacketizedAudioStream that decodes AAC sound
 *
 * @param extraData  The stream containing the extra data needed for initialization
 * @return             A new PacketizedAudioStream, or NULL on error
 */
PacketizedAudioStream *makeAACStream(Common::SeekableReadStream &extraData);

} // End of namespace Audio

#endif // #ifdef USE_FAAD
#endif // #ifndef AUDIO_AAC_H
