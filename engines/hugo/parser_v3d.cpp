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
 * $URL$
 * $Id$
 *
 */

/*
 * This code is based on original Hugo Trilogy source code
 *
 * Copyright (c) 1989-1995 David P. Gray
 *
 */

// parser.c - handles all keyboard/command input

#include "common/system.h"

#include "hugo/hugo.h"
#include "hugo/parser.h"
#include "hugo/file.h"
#include "hugo/schedule.h"
#include "hugo/util.h"
#include "hugo/sound.h"
#include "hugo/object.h"
#include "hugo/text.h"

namespace Hugo {

Parser_v3d::Parser_v3d(HugoEngine *vm) : Parser_v1d(vm) {
}

Parser_v3d::~Parser_v3d() {
}

/**
 * Parse the user's line of text input.  Generate events as necessary
 */
void Parser_v3d::lineHandler() {
	debugC(1, kDebugParser, "lineHandler()");

	status_t &gameStatus = _vm->getGameStatus();

	// Toggle God Mode
	if (!strncmp(_vm->_line, "PPG", 3)) {
		_vm->_sound->playSound(!_vm->_soundTest, kSoundPriorityHigh);
		gameStatus.godModeFl = !gameStatus.godModeFl;
		return;
	}

	Utils::strlwr(_vm->_line);                      // Convert to lower case

	// God Mode cheat commands:
	// goto <screen>                                Takes hero to named screen
	// fetch <object name>                          Hero carries named object
	// fetch all                                    Hero carries all possible objects
	// find <object name>                           Takes hero to screen containing named object
	if (gameStatus.godModeFl) {
		// Special code to allow me to go straight to any screen
		if (strstr(_vm->_line, "goto")) {
			for (int i = 0; i < _vm->_numScreens; i++) {
				if (!scumm_stricmp(&_vm->_line[strlen("goto") + 1], _vm->_text->getScreenNames(i))) {
					_vm->_scheduler->newScreen(i);
					return;
				}
			}
		}

		// Special code to allow me to get objects from anywhere
		if (strstr(_vm->_line, "fetch all")) {
			for (int i = 0; i < _vm->_object->_numObj; i++) {
				if (_vm->_object->_objects[i].genericCmd & TAKE)
					takeObject(&_vm->_object->_objects[i]);
			}
			return;
		}

		if (strstr(_vm->_line, "fetch")) {
			for (int i = 0; i < _vm->_object->_numObj; i++) {
				if (!scumm_stricmp(&_vm->_line[strlen("fetch") + 1], _vm->_text->getNoun(_vm->_object->_objects[i].nounIndex, 0))) {
					takeObject(&_vm->_object->_objects[i]);
					return;
				}
			}
		}

		// Special code to allow me to goto objects
		if (strstr(_vm->_line, "find")) {
			for (int i = 0; i < _vm->_object->_numObj; i++) {
				if (!scumm_stricmp(&_vm->_line[strlen("find") + 1], _vm->_text->getNoun(_vm->_object->_objects[i].nounIndex, 0))) {
					_vm->_scheduler->newScreen(_vm->_object->_objects[i].screenIndex);
					return;
				}
			}
		}
	}

	// Special meta commands
	// EXIT/QUIT
	if (!strcmp("exit", _vm->_line) || strstr(_vm->_line, "quit")) {
		if (Utils::yesNoBox(_vm->_text->getTextParser(kTBExit_1d)))
			_vm->endGame();
		return;
	}

	// SAVE/RESTORE
	if (!strcmp("save", _vm->_line)) {
		_vm->_config.soundFl = false;
		if (gameStatus.gameOverFl)
			_vm->gameOverMsg();
		else
			_vm->_file->saveGame(-1, Common::String());
		return;
	}

	if (!strcmp("restore", _vm->_line)) {
		_vm->_config.soundFl = false;
		_vm->_file->restoreGame(-1);
		return;
	}

	// Empty line
	if (*_vm->_line == '\0')                        // Empty line
		return;
	if (strspn(_vm->_line, " ") == strlen(_vm->_line)) // Nothing but spaces!
		return;

	if (gameStatus.gameOverFl) {
		// No commands allowed!
		_vm->gameOverMsg();
		return;
	}

	char farComment[kCompLineSize * 5] = "";        // hold 5 line comment if object not nearby

	// Test for nearby objects referenced explicitly
	for (int i = 0; i < _vm->_object->_numObj; i++) {
		object_t *obj = &_vm->_object->_objects[i];
		if (isWordPresent(_vm->_text->getNounArray(obj->nounIndex))) {
			if (isObjectVerb_v3(obj, farComment) || isGenericVerb_v3(obj, farComment))
				return;
		}
	}

	// Test for nearby objects that only require a verb
	// Note comment is unused if not near.
	for (int i = 0; i < _vm->_object->_numObj; i++) {
		object_t *obj = &_vm->_object->_objects[i];
		if (obj->verbOnlyFl) {
			char contextComment[kCompLineSize * 5] = ""; // Unused comment for context objects
			if (isObjectVerb_v3(obj, contextComment) || isGenericVerb_v3(obj, contextComment))
				return;
		}
	}

	// No objects match command line, try background and catchall commands
	if (isBackgroundWord_v3(_backgroundObjects[*_vm->_screen_p]))
		return;
	if (isCatchallVerb_v3(_backgroundObjects[*_vm->_screen_p]))
		return;

	if (isBackgroundWord_v3(_catchallList))
		return;
	if (isCatchallVerb_v3(_catchallList))
		return;

	// If a not-near comment was generated, print it
	if (*farComment != '\0') {
		Utils::Box(kBoxAny, "%s", farComment);
		return;
	}

	// Nothing matches.  Report recognition success to user.
	const char *verb = findVerb();
	const char *noun = findNoun();

	if (verb && noun) {                             // A combination I didn't think of
		Utils::Box(kBoxAny, "%s", _vm->_text->getTextParser(kTBNoPoint));
	} else if (noun) {
		Utils::Box(kBoxAny, "%s", _vm->_text->getTextParser(kTBNoun));
	} else if (verb) {
		Utils::Box(kBoxAny, "%s", _vm->_text->getTextParser(kTBVerb));
	} else {
		Utils::Box(kBoxAny, "%s", _vm->_text->getTextParser(kTBEh));
	}
}

/**
 * Test whether command line contains a verb allowed by this object.
 * If it does, and the object is near and passes the tests in the command
 * list then carry out the actions in the action list and return TRUE
 */
bool Parser_v3d::isObjectVerb_v3(object_t *obj, char *comment) {
	debugC(1, kDebugParser, "isObjectVerb(object_t *obj, %s)", comment);

	// First, find matching verb in cmd list
	uint16 cmdIndex = obj->cmdIndex;                // ptr to list of commands
	if (cmdIndex == 0)                              // No commands for this obj
		return false;

	int i;
	for (i = 0; _cmdList[cmdIndex][i].verbIndex != 0; i++) {                           // For each cmd
		if (isWordPresent(_vm->_text->getVerbArray(_cmdList[cmdIndex][i].verbIndex)))  // Was this verb used?
			break;
	}

	if (_cmdList[cmdIndex][i].verbIndex == 0)       // No verbs used.
		return false;

	// Verb match found.  Check if object is Near
	char *verb = *_vm->_text->getVerbArray(_cmdList[cmdIndex][i].verbIndex);
	if (!isNear_v3(obj, verb, comment))
		return false;

	// Check all required objects are being carried
	cmd *cmnd = &_cmdList[cmdIndex][i];             // ptr to struct cmd
	if (cmnd->reqIndex) {                           // At least 1 thing in list
		uint16 *reqs = _arrayReqs[cmnd->reqIndex];  // ptr to list of required objects
		for (i = 0; reqs[i]; i++) {                 // for each obj
			if (!_vm->_object->isCarrying(reqs[i])) {
				Utils::Box(kBoxAny, "%s", _vm->_text->getTextData(cmnd->textDataNoCarryIndex));
				return true;
			}
		}
	}

	// Required objects are present, now check state is correct
	if ((obj->state != cmnd->reqState) && (cmnd->reqState != kStateDontCare)) {
		Utils::Box(kBoxAny, "%s", _vm->_text->getTextData(cmnd->textDataWrongIndex));
		return true;
	}

	// Everything checked.  Change the state and carry out any actions
	if (cmnd->reqState != kStateDontCare)           // Don't change new state if required state didn't care
		obj->state = cmnd->newState;
	Utils::Box(kBoxAny, "%s", _vm->_text->getTextData(cmnd->textDataDoneIndex));
	_vm->_scheduler->insertActionList(cmnd->actIndex);

	// See if any additional generic actions
	if ((verb == _vm->_text->getVerb(_vm->_look, 0)) || (verb == _vm->_text->getVerb(_vm->_take, 0)) || (verb == _vm->_text->getVerb(_vm->_drop, 0)))
		isGenericVerb_v3(obj, comment);
	return true;
}

/**
 * Test whether command line contains one of the generic actions
 */
bool Parser_v3d::isGenericVerb_v3(object_t *obj, char *comment) {
	debugC(1, kDebugParser, "isGenericVerb(object_t *obj, %s)", comment);

	if (!obj->genericCmd)
		return false;

	// Following is equivalent to switch, but couldn't do one
	if (isWordPresent(_vm->_text->getVerbArray(_vm->_look)) && isNear_v3(obj, _vm->_text->getVerb(_vm->_look, 0), comment)) {
		// Test state-dependent look before general look
		if ((obj->genericCmd & LOOK_S) == LOOK_S) {
			Utils::Box(kBoxAny, "%s", _vm->_text->getTextData(obj->stateDataIndex[obj->state]));
		} else {
			if ((LOOK & obj->genericCmd) == LOOK) {
				if (obj->dataIndex != 0)
					Utils::Box(kBoxAny, "%s", _vm->_text->getTextData(obj->dataIndex));
				else
					return false;
			} else {
				Utils::Box(kBoxAny, "%s", _vm->_text->getTextParser(kTBUnusual));
			}
		}
	} else if (isWordPresent(_vm->_text->getVerbArray(_vm->_take)) && isNear_v3(obj, _vm->_text->getVerb(_vm->_take, 0), comment)) {
		if (obj->carriedFl)
			Utils::Box(kBoxAny, "%s", _vm->_text->getTextParser(kTBHave));
		else if ((TAKE & obj->genericCmd) == TAKE)
			takeObject(obj);
		else if (obj->cmdIndex)                     // No comment if possible commands
			return false;
		else if (!obj->verbOnlyFl && (TAKE & obj->genericCmd) == TAKE)  // Make sure not taking object in context!
			Utils::Box(kBoxAny, "%s", _vm->_text->getTextParser(kTBNoUse));
		else
			return false;
	} else if (isWordPresent(_vm->_text->getVerbArray(_vm->_drop))) {
		if (!obj->carriedFl && ((DROP & obj->genericCmd) == DROP))
			Utils::Box(kBoxAny, "%s", _vm->_text->getTextParser(kTBDontHave));
		else if (obj->carriedFl && ((DROP & obj->genericCmd) == DROP))
			dropObject(obj);
		else if (obj->cmdIndex == 0)
			Utils::Box(kBoxAny, "%s", _vm->_text->getTextParser(kTBNeed));
		else
			return false;
	} else {                                        // It was not a generic cmd
		return false;
	}

	return true;
}

/**
 * Test whether hero is close to object.  Return TRUE or FALSE
 * If object not near, return suitable comment; may be another object close
 * If radius is -1, treat radius as infinity
 * Verb is included to determine correct comment if not near
 */
bool Parser_v3d::isNear_v3(object_t *obj, const char *verb, char *comment) const {
	debugC(1, kDebugParser, "isNear(object_t *obj, %s, %s)", verb, comment);

	if (obj->carriedFl)                             // Object is being carried
		return true;

	if (obj->screenIndex != *_vm->_screen_p) {
		// Not in same screen
		if (obj->objValue)
			strcpy(comment, _vm->_text->getTextParser(kCmtAny1));
		else
			strcpy(comment, _vm->_text->getTextParser(kCmtAny2));
		return false;
	}

	if (obj->cycling == kCycleInvisible) {
		if (obj->seqNumb) {
			// There is an image
			strcpy(comment, _vm->_text->getTextParser(kCmtAny3));
			return false;
		} else {
			// No image, assume visible
			if ((obj->radius < 0) ||
			        ((abs(obj->x - _vm->_hero->x) <= obj->radius) &&
					(abs(obj->y - _vm->_hero->y - _vm->_hero->currImagePtr->y2) <= obj->radius))) {
				return true;
			} else {
				// User is not close enough
				if (obj->objValue && (verb != _vm->_text->getVerb(_vm->_take, 0)))
					strcpy(comment, _vm->_text->getTextParser(kCmtAny1));
				else
					strcpy(comment, _vm->_text->getTextParser(kCmtClose));
				return false;
			}
		}
	}

	if ((obj->radius < 0) ||
	    ((abs(obj->x - _vm->_hero->x) <= obj->radius) &&
	     (abs(obj->y + obj->currImagePtr->y2 - _vm->_hero->y - _vm->_hero->currImagePtr->y2) <= obj->radius))) {
		return true;
	} else {
		// User is not close enough
		if (obj->objValue && (verb != _vm->_text->getVerb(_vm->_take, 0)))
			strcpy(comment, _vm->_text->getTextParser(kCmtAny1));
		else
			strcpy(comment, _vm->_text->getTextParser(kCmtClose));
		return false;
	}
	return true;
}

/**
 * Do all things necessary to carry an object
 */
void Parser_v3d::takeObject(object_t *obj) {
	debugC(1, kDebugParser, "takeObject(object_t *obj)");

	obj->carriedFl = true;
	if (obj->seqNumb) {                             // Don't change if no image to display
		obj->cycling = kCycleInvisible;
	}
	_vm->adjustScore(obj->objValue);

	if (obj->seqNumb > 0)                           // If object has an image, force walk to dropped
		obj->viewx = -1;                            // (possibly moved) object next time taken!
	Utils::Box(kBoxAny, TAKE_TEXT, _vm->_text->getNoun(obj->nounIndex, TAKE_NAME));
}

/**
 * Do all necessary things to drop an object
 */
void Parser_v3d::dropObject(object_t *obj) {
	debugC(1, kDebugParser, "dropObject(object_t *obj)");

	obj->carriedFl = false;
	obj->screenIndex = *_vm->_screen_p;
	if ((obj->seqNumb > 1) || (obj->seqList[0].imageNbr > 1))
		obj->cycling = kCycleForward;
	else
		obj->cycling = kCycleNotCycling;
	obj->x = _vm->_hero->x - 1;
	obj->y = _vm->_hero->y + _vm->_hero->currImagePtr->y2 - 1;
	obj->y = (obj->y + obj->currImagePtr->y2 < kYPix) ? obj->y : kYPix - obj->currImagePtr->y2 - 10;
	_vm->adjustScore(-obj->objValue);
	Utils::Box(kBoxAny, "%s", _vm->_text->getTextParser(kTBOk));
}

/**
 * Search for matching verbs in background command list.
 * Noun is not required.  Return TRUE if match found
 * Note that if the background command list has match set TRUE then do not
 * print text if there are any recognizable nouns in the command line
 */
bool Parser_v3d::isCatchallVerb_v3(objectList_t obj) const {
	debugC(1, kDebugParser, "isCatchallVerb(object_list_t obj)");

	if (_vm->_maze.enabledFl)
		return false;

	for (int i = 0; obj[i].verbIndex != 0; i++) {
		if (isWordPresent(_vm->_text->getVerbArray(obj[i].verbIndex)) && obj[i].nounIndex == 0 &&
		   (!obj[i].matchFl || !findNoun()) &&
		   ((obj[i].roomState == kStateDontCare) ||
		    (obj[i].roomState == _vm->_screenStates[*_vm->_screen_p]))) {
			Utils::Box(kBoxAny, "%s", _vm->_file->fetchString(obj[i].commentIndex));
			_vm->_scheduler->processBonus(obj[i].bonusIndex);

			// If this is LOOK (without a noun), show any takeable objects
			if (*(_vm->_text->getVerbArray(obj[i].verbIndex)) == _vm->_text->getVerb(_vm->_look, 0))
				_vm->_object->showTakeables();

			return true;
		}
	}
	return false;
}

/**
 * Search for matching verb/noun pairs in background command list
 * Print text for possible background object.  Return TRUE if match found
 */
bool Parser_v3d::isBackgroundWord_v3(objectList_t obj) const {
	debugC(1, kDebugParser, "isBackgroundWord(object_list_t obj)");

	if (_vm->_maze.enabledFl)
		return false;

	for (int i = 0; obj[i].verbIndex != 0; i++) {
		if (isWordPresent(_vm->_text->getVerbArray(obj[i].verbIndex)) &&
		    isWordPresent(_vm->_text->getNounArray(obj[i].nounIndex)) &&
		    ((obj[i].roomState == kStateDontCare) ||
		     (obj[i].roomState == _vm->_screenStates[*_vm->_screen_p]))) {
			Utils::Box(kBoxAny, "%s", _vm->_file->fetchString(obj[i].commentIndex));
			_vm->_scheduler->processBonus(obj[i].bonusIndex);
			return true;
		}
	}
	return false;
}

} // End of namespace Hugo
