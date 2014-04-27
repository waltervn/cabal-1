/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "common/scummsys.h"
#include "common/config-manager.h"
#include "mads/mads.h"
#include "mads/compression.h"
#include "mads/resources.h"
#include "mads/scene.h"
#include "mads/phantom/game_phantom.h"
#include "mads/phantom/phantom_scenes.h"

namespace MADS {

namespace Phantom {

SceneLogic *SceneFactory::createScene(MADSEngine *vm) {
	Scene &scene = vm->_game->_scene;

	// TODO
	//scene.addActiveVocab(NOUN_DROP);

	// TODO: Just return a dummy scene for now
	return new DummyScene(vm);

	switch (scene._nextSceneId) {
	// Scene group #1
	case 101:
	// TODO

	// Scene group #2
	// TODO

	// Scene group #3
	// TODO

	// Scene group #8
	// TODO

	default:
		error("Invalid scene %d called", scene._nextSceneId);
	}
}

/*------------------------------------------------------------------------*/

PhantomScene::PhantomScene(MADSEngine *vm) : SceneLogic(vm),
		_globals(static_cast<GamePhantom *>(vm->_game)->_globals),
		_game(*static_cast<GamePhantom *>(vm->_game)),
		_action(vm->_game->_scene._action) {
}

Common::String PhantomScene::formAnimName(char sepChar, int suffixNum) {
	return Resources::formatName(_scene->_currentSceneId, sepChar, suffixNum,
		EXT_NONE, "");
}

/*------------------------------------------------------------------------*/

void SceneInfoPhantom::loadCodes(MSurface &depthSurface, int variant) {
	File f(Resources::formatName(RESPREFIX_RM, _sceneId, ".DAT"));
	MadsPack codesPack(&f);
	Common::SeekableReadStream *stream = codesPack.getItemStream(variant + 1);

	loadCodes(depthSurface, stream);

	delete stream;
	f.close();
}

void SceneInfoPhantom::loadCodes(MSurface &depthSurface, Common::SeekableReadStream *stream) {
	byte *destP = depthSurface.getData();
	byte *endP = depthSurface.getBasePtr(0, depthSurface.h);

	byte runLength = stream->readByte();
	while (destP < endP && runLength > 0) {
		byte runValue = stream->readByte();

		// Write out the run length
		Common::fill(destP, destP + runLength, runValue);
		destP += runLength;

		// Get the next run length
		runLength = stream->readByte();
	}

	if (destP < endP)
		Common::fill(destP, endP, 0);
}

} // End of namespace Phantom

} // End of namespace MADS
