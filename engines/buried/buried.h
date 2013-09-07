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

#ifndef BURIED_BURIED_H
#define BURIED_BURIED_H

#include "common/scummsys.h"
#include "common/array.h"
#include "common/list.h"
#include "common/hashmap.h"

#include "engines/engine.h"

class OSystem;

namespace Common {
class SeekableReadStream;
}

namespace Buried {

struct BuriedGameDescription;
class Database;
class GraphicsManager;
class Message;
class SoundManager;
class Window;
class VideoWindow;

class BuriedEngine : public ::Engine {
protected:
	Common::Error run();

public:
	BuriedEngine(OSystem *syst, const BuriedGameDescription *gamedesc);
	virtual ~BuriedEngine();

	// Detection related functions
	const BuriedGameDescription *_gameDescription;
	bool isDemo() const;
	bool isTrueColor() const;
	bool isWin95() const;
	bool isCompressed() const;
	Common::String getEXEName() const;
	Common::String getLibraryName() const;

	bool hasFeature(EngineFeature f) const;

	// Resources
	Common::String getString(uint32 stringID);
	Common::String getFilePath(uint32 stringID);
	Common::SeekableReadStream *getBitmapStream(uint32 bitmapID);
	Common::SeekableReadStream *getNavData(uint32 resourceID);
	Common::SeekableReadStream *getSndData(uint32 resourceID);
	Common::SeekableReadStream *getAnimData(uint32 resourceID);
	Common::SeekableReadStream *getAIData(uint32 resourceID);
	Common::SeekableReadStream *getItemData(uint32 resourceID);
	Common::SeekableReadStream *getBookData(uint32 resourceID);
	Common::SeekableReadStream *getFileBCData(uint32 resourceID);
	Common::SeekableReadStream *getINNData(uint32 resourceID);

	GraphicsManager *_gfx;
	Database *_mainEXE;
	SoundManager *_sound;
	Window *_mainWindow; // Only one main window is supported.
	Window *_focusedWindow;

	// Timers
	uint createTimer(Window *window, uint period);
	bool killTimer(uint timer);
	void updateTimers();

	// Video
	void addVideo(VideoWindow *window);
	void removeVideo(VideoWindow *window);
	void updateVideos();

	// Messaging
	void postMessageToWindow(Window *dest, Message *message);
	void sendAllMessages();
	void removeKeyboardMessages(Window *window);
	void removeMouseMessages(Window *window);
	void removeAllMessages(Window *window);

private:
	Database *_library;

	struct Timer {
		Window *owner;
		uint32 period;
		uint32 nextTrigger;
	};

	typedef Common::HashMap<uint, Timer> TimerMap;
	TimerMap _timers;
	uint _timerSeed;

	typedef Common::List<VideoWindow *> VideoList;
	VideoList _videos;

	struct MessageInfo { // I did think about calling this "Envelope"
		Window *dest;
		Message *message;
	};

	// LordHoto didn't want me to add an iterator to Common::Queue.
	typedef Common::List<MessageInfo> MessageQueue;
	MessageQueue _messageQueue;
};

} // End of namespace Buried

#endif
