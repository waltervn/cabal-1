/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * Additional copyright for this file:
 * Copyright (C) 1995-1997 Presto Studios, Inc.
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

#include "pegasus/gamestate.h"
#include "pegasus/menu.h"
#include "pegasus/pegasus.h"
#include "pegasus/scoring.h"

namespace Pegasus {

GameMenu::GameMenu(const uint32 id) : IDObject(id), InputHandler((InputHandler *)((PegasusEngine *)g_engine)) {
	_previousHandler = 0;
	_lastCommand = kMenuCmdNoCommand;
}

void GameMenu::becomeCurrentHandler() {
	_previousHandler = InputHandler::setInputHandler(this);
}

void GameMenu::restorePreviousHandler() {
	InputHandler::setInputHandler(_previousHandler);
}

void GameMenu::drawScore(tGameScoreType score, tGameScoreType total, const Common::Rect &scoreBounds, Surface *numbers) {
	tCoordType x = scoreBounds.right;
	drawNumber(total, x, scoreBounds.top, numbers);

	x -= 12;
	Common::Rect r1(120, 0, 132, 12); // The slash.
	Common::Rect r2 = r1;
	r2.moveTo(x, scoreBounds.top);
	numbers->copyToCurrentPort(r1, r2);
	drawNumber(score, x, scoreBounds.top, numbers);
}

void GameMenu::drawNumber(tGameScoreType number, tCoordType &x, tCoordType y, Surface *numbers) {
	Common::Rect r1(0, 0, 12, 12); // Width, height of one digit
	Common::Rect r2 = r1;
	r2.moveTo(x - 12, y);

	do {
		uint16 digit = number % 10;
		number /= 10;
		r1.moveTo(digit * 12, 0);
		numbers->copyToCurrentPort(r1, r2);
		r2.translate(-12, 0);
	} while (number != 0);

	x = r2.right;
}

enum {
	kMainMenuStartDemo = 0,
	kMainMenuCreditsDemo,
	kMainMenuQuitDemo,
	kFirstSelectionDemo = kMainMenuStartDemo,
	kLastSelectionDemo = kMainMenuQuitDemo,

	kMainMenuOverview = 0,
	kMainMenuStart,
	kMainMenuRestore,
	kMainMenuDifficulty,
	kMainMenuCredits,
	kMainMenuQuit,
	kFirstSelection = kMainMenuOverview,
	kLastSelection = kMainMenuQuit
};

static const tCoordType kStartLeftDemo = 44;
static const tCoordType kStartTopDemo = 336;

static const tCoordType kStartSelectLeftDemo = 40;
static const tCoordType kStartSelectTopDemo = 331;

static const tCoordType kCreditsLeftDemo = 44;
static const tCoordType kCreditsTopDemo = 372;

static const tCoordType kCreditsSelectLeftDemo = 40;
static const tCoordType kCreditsSelectTopDemo = 367;

static const tCoordType kMainMenuQuitLeftDemo = 32;
static const tCoordType kMainMenuQuitTopDemo = 412;

static const tCoordType kMainMenuQuitSelectLeftDemo = 28;
static const tCoordType kMainMenuQuitSelectTopDemo = 408;

static const tCoordType kOverviewLeft = 200;
static const tCoordType kOverviewTop = 208;

static const tCoordType kOverviewSelectLeft = 152;
static const tCoordType kOverviewSelectTop = 204;

static const tCoordType kStartLeft = 212;
static const tCoordType kStartTop = 256;

static const tCoordType kStartSelectLeft = 152;
static const tCoordType kStartSelectTop = 252;

static const tCoordType kRestoreLeft = 212;
static const tCoordType kRestoreTop = 296;

static const tCoordType kRestoreSelectLeft = 152;
static const tCoordType kRestoreSelectTop = 292;

static const tCoordType kDifficultyLeft = 320;
static const tCoordType kDifficultyTop = 340;

static const tCoordType kDifficultySelectLeft = 152;
static const tCoordType kDifficultySelectTop = 336;

static const tCoordType kCreditsLeft = 212;
static const tCoordType kCreditsTop = 388;

static const tCoordType kCreditsSelectLeft = 152;
static const tCoordType kCreditsSelectTop = 384;

static const tCoordType kMainMenuQuitLeft = 212;
static const tCoordType kMainMenuQuitTop = 428;

static const tCoordType kMainMenuQuitSelectLeft = 152;
static const tCoordType kMainMenuQuitSelectTop = 424;

//	Never set the current input handler to the MainMenu.
MainMenu::MainMenu() : GameMenu(kMainMenuID), _menuBackground(0), _overviewButton(0),
		_restoreButton(0), _adventureButton(0), _walkthroughButton(0), _startButton(0),
		_creditsButton(0), _quitButton(0), _largeSelect(0), _smallSelect(0) {

	bool isDemo = ((PegasusEngine *)g_engine)->isDemo();

	if (isDemo)
		_menuBackground.initFromPICTFile("Images/Demo/DemoMenu.pict");
	else
		_menuBackground.initFromPICTFile("Images/Main Menu/MainMenu.mac");
	_menuBackground.setDisplayOrder(0);
	_menuBackground.startDisplaying();
	_menuBackground.show();

	if (!isDemo) {
		_overviewButton.initFromPICTFile("Images/Main Menu/pbOvervi.pict");
		_overviewButton.setDisplayOrder(1);
		_overviewButton.moveElementTo(kOverviewLeft, kOverviewTop);
		_overviewButton.startDisplaying();

		_restoreButton.initFromPICTFile("Images/Main Menu/pbRestor.pict");
		_restoreButton.setDisplayOrder(1);
		_restoreButton.moveElementTo(kRestoreLeft, kRestoreTop);
		_restoreButton.startDisplaying();

		_adventureButton.initFromPICTFile("Images/Main Menu/BtnAdv.pict");
		_adventureButton.setDisplayOrder(1);
		_adventureButton.moveElementTo(kDifficultyLeft, kDifficultyTop);
		_adventureButton.startDisplaying();

		_walkthroughButton.initFromPICTFile("Images/Main Menu/BtnWlk.pict");
		_walkthroughButton.setDisplayOrder(1);
		_walkthroughButton.moveElementTo(kDifficultyLeft, kDifficultyTop);
		_walkthroughButton.startDisplaying();
	}

	if (isDemo)
		_startButton.initFromPICTFile("Images/Demo/Start.pict");
	else
		_startButton.initFromPICTFile("Images/Main Menu/pbStart.pict");
	_startButton.setDisplayOrder(1);
	_startButton.moveElementTo(isDemo ? kStartLeftDemo : kStartLeft, isDemo ? kStartTopDemo : kStartTop);
	_startButton.startDisplaying();

	if (isDemo)
		_creditsButton.initFromPICTFile("Images/Demo/Credits.pict");
	else
		_creditsButton.initFromPICTFile("Images/Main Menu/pbCredit.pict");
	_creditsButton.setDisplayOrder(1);
	_creditsButton.moveElementTo(isDemo ? kCreditsLeftDemo : kCreditsLeft, isDemo ? kCreditsTopDemo : kCreditsTop);
	_creditsButton.startDisplaying();

	if (isDemo)
		_quitButton.initFromPICTFile("Images/Demo/Quit.pict");
	else
		_quitButton.initFromPICTFile("Images/Main Menu/pbQuit.pict");
	_quitButton.setDisplayOrder(1);
	_quitButton.moveElementTo(isDemo ? kMainMenuQuitLeftDemo : kMainMenuQuitLeft, isDemo ? kMainMenuQuitTopDemo : kMainMenuQuitTop);
	_quitButton.startDisplaying();

	if (isDemo)
		_largeSelect.initFromPICTFile("Images/Demo/SelectL.pict", true);
	else
		_largeSelect.initFromPICTFile("Images/Main Menu/SelectL.pict", true);
	_largeSelect.setDisplayOrder(1);
	_largeSelect.startDisplaying();

	if (isDemo)
		_smallSelect.initFromPICTFile("Images/Demo/SelectS.pict", true);
	else
		_smallSelect.initFromPICTFile("Images/Main Menu/SelectS.pict", true);
	_smallSelect.setDisplayOrder(1);
	_smallSelect.startDisplaying();

	_menuSelection = isDemo ? kFirstSelectionDemo : kFirstSelection;

	_adventureMode = true;

	_menuLoop.attachFader(&_menuFader);
	_menuLoop.initFromAIFFFile("Sounds/Main Menu.aiff");

	updateDisplay();
}

MainMenu::~MainMenu() {
	if (_menuLoop.isPlaying())
		stopMainMenuLoop();
}

void MainMenu::startMainMenuLoop() {
	FaderMoveSpec spec;

	_menuLoop.loopSound();
	spec.makeTwoKnotFaderSpec(30, 0, 0, 30, 255);
	_menuFader.startFaderSync(spec);
}

void MainMenu::stopMainMenuLoop() {
	FaderMoveSpec spec;
	
	spec.makeTwoKnotFaderSpec(30, 0, 255, 30, 0);
	_menuFader.startFaderSync(spec);
	_menuLoop.stopSound();
}

void MainMenu::handleInput(const Input &input, const Hotspot *cursorSpot) {
	PegasusEngine *vm = (PegasusEngine *)g_engine;
	bool isDemo = vm->isDemo();

	if (input.upButtonDown()) {
		if (_menuSelection > (isDemo ? kFirstSelectionDemo : kFirstSelection)) {
			_menuSelection--;
			updateDisplay();
		}
	} else if (input.downButtonDown()) {
		if (_menuSelection < (isDemo ? kLastSelectionDemo : kLastSelection)) {
			_menuSelection++;
			updateDisplay();
		}
	} else if (!isDemo && (input.leftButtonDown() || input.rightButtonDown())) {
		if (_menuSelection == kMainMenuDifficulty) {
			_adventureMode = !_adventureMode;
			updateDisplay();
		}
	} else if (JMPPPInput::isMenuButtonPressInput(input)) {
		if (isDemo) {
			switch (_menuSelection) {
			case kMainMenuCreditsDemo:
				_creditsButton.show();
				vm->delayShell(kMenuButtonHiliteTime, kMenuButtonHiliteScale);
				_creditsButton.hide();
				setLastCommand(kMenuCmdCredits);
				break;
			case kMainMenuStartDemo:
				_startButton.show();
				vm->delayShell(kMenuButtonHiliteTime, kMenuButtonHiliteScale);
				_startButton.hide();
				setLastCommand(kMenuCmdStartAdventure);
				break;
			case kMainMenuQuitDemo:
				_quitButton.show();
				vm->delayShell(kMenuButtonHiliteTime, kMenuButtonHiliteScale);
				_quitButton.hide();
				setLastCommand(kMenuCmdQuit);
				break;
			}
		} else {
			switch (_menuSelection) {
			case kMainMenuOverview:
				_overviewButton.show();
				vm->delayShell(kMenuButtonHiliteTime, kMenuButtonHiliteScale);
				_overviewButton.hide();
				setLastCommand(kMenuCmdOverview);
				break;
			case kMainMenuRestore:
				_restoreButton.show();
				vm->delayShell(kMenuButtonHiliteTime, kMenuButtonHiliteScale);
				_restoreButton.hide();
				setLastCommand(kMenuCmdRestore);
				break;
			case kMainMenuCredits:
				_creditsButton.show();
				vm->delayShell(kMenuButtonHiliteTime, kMenuButtonHiliteScale);
				_creditsButton.hide();
				setLastCommand(kMenuCmdCredits);
				break;
			case kMainMenuStart:
				_startButton.show();
				vm->delayShell(kMenuButtonHiliteTime, kMenuButtonHiliteScale);
				_startButton.hide();
				if (_adventureMode)
					setLastCommand(kMenuCmdStartAdventure);
				else
					setLastCommand(kMenuCmdStartWalkthrough);
				break;
			case kMainMenuDifficulty:
				_adventureMode = !_adventureMode;
				updateDisplay();
				break;
			case kMainMenuQuit:
				_quitButton.show();
				vm->delayShell(kMenuButtonHiliteTime, kMenuButtonHiliteScale);
				_quitButton.hide();
				setLastCommand(kMenuCmdQuit);
				break;
			}
		}
	}

	InputHandler::handleInput(input, cursorSpot);
}

void MainMenu::updateDisplay() {
	PegasusEngine *vm = (PegasusEngine *)g_engine;

	if (vm->isDemo()) {
		switch (_menuSelection) {
		case kMainMenuStartDemo:
			_smallSelect.moveElementTo(kStartSelectLeftDemo, kStartSelectTopDemo);
			_smallSelect.show();
			_largeSelect.hide();
			break;
		case kMainMenuCreditsDemo:
			_smallSelect.moveElementTo(kCreditsSelectLeftDemo, kCreditsSelectTopDemo);
			_smallSelect.show();
			_largeSelect.hide();
			break;
		case kMainMenuQuitDemo:
			_largeSelect.moveElementTo(kMainMenuQuitSelectLeftDemo, kMainMenuQuitSelectTopDemo);
			_largeSelect.show();
			_smallSelect.hide();
			break;
		}
	} else {
		switch (_menuSelection) {
		case kMainMenuOverview:
			_largeSelect.moveElementTo(kOverviewSelectLeft, kOverviewSelectTop);
			_largeSelect.show();
			_smallSelect.hide();
			break;
		case kMainMenuRestore:
			_smallSelect.moveElementTo(kRestoreSelectLeft, kRestoreSelectTop);
			_smallSelect.show();
			_largeSelect.hide();
			break;
		case kMainMenuDifficulty:
			if (_adventureMode) {
				_adventureButton.show();
				_walkthroughButton.hide();
			} else {
				_walkthroughButton.show();
				_adventureButton.hide();
			}

			_largeSelect.moveElementTo(kDifficultySelectLeft, kDifficultySelectTop);
			_largeSelect.show();
			_smallSelect.hide();
			break;
		case kMainMenuStart:
			_smallSelect.moveElementTo(kStartSelectLeft, kStartSelectTop);
			_smallSelect.show();
			_largeSelect.hide();
			break;
		case kMainMenuCredits:
			_smallSelect.moveElementTo(kCreditsSelectLeft, kCreditsSelectTop);
			_smallSelect.show();
			_largeSelect.hide();
			break;
		case kMainMenuQuit:
			_smallSelect.moveElementTo(kMainMenuQuitSelectLeft, kMainMenuQuitSelectTop);
			_smallSelect.show();
			_largeSelect.hide();
			break;
		}

		vm->resetIntroTimer();
	}
}

enum {
	kCreditsMenuCoreTeam,
	kCreditsMenuSupportTeam,
	kCreditsMenuOriginalTeam,
	kCreditsMenuTalent,
	kCreditsMenuOtherTitles,
	kCreditsMenuMainMenu,
	
	kCreditsFirstSelection = kCreditsMenuCoreTeam,
	kCreditsLastSelection = kCreditsMenuMainMenu
};

static const tCoordType kCreditsMovieLeft = 288;
static const tCoordType kCreditsMovieTop = 0;

static const tCoordType kCoreTeamSelectLeft = 40;
static const tCoordType kCoreTeamSelectTop = 223;

static const tCoordType kSupportTeamSelectLeft = 40;
static const tCoordType kSupportTeamSelectTop = 259;

static const tCoordType kOriginalTeamSelectLeft = 40;
static const tCoordType kOriginalTeamSelectTop = 295;

static const tCoordType kTalentSelectLeft = 40;
static const tCoordType kTalentSelectTop = 331;

static const tCoordType kOtherTitlesSelectLeft = 40;
static const tCoordType kOtherTitlesSelectTop = 367;

static const tCoordType kCreditsMainMenuLeft = 32;
static const tCoordType kCreditsMainMenuTop = 412;

static const tCoordType kCreditsMainMenuSelectLeft = 30;
static const tCoordType kCreditsMainMenuSelectTop = 408;

static const TimeValue kCoreTeamTime = 0;
static const TimeValue kSupportTeamTime = 1920;
static const TimeValue kOriginalTeamTime = 3000;
static const TimeValue kTalentTime = 4440;
static const TimeValue kOtherTitlesTime = 4680;

static const TimeValue kFrameIncrement = 120;		//	Three frames...

//	Never set the current input handler to the CreditsMenu.
CreditsMenu::CreditsMenu() : GameMenu(kCreditsMenuID), _menuBackground(0), _creditsMovie(0),
		_mainMenuButton(0), _largeSelect(0), _smallSelect(0) {

	_menuBackground.initFromPICTFile("Images/Credits/CredScrn.pict");
	_menuBackground.setDisplayOrder(0);
	_menuBackground.startDisplaying();
	_menuBackground.show();

	_creditsMovie.initFromMovieFile("Images/Credits/Credits.movie");
	_creditsMovie.setDisplayOrder(1);
	_creditsMovie.moveElementTo(kCreditsMovieLeft, kCreditsMovieTop);
	_creditsMovie.startDisplaying();
	_creditsMovie.show();
	_creditsMovie.redrawMovieWorld();

	_mainMenuButton.initFromPICTFile("Images/Credits/MainMenu.pict");
	_mainMenuButton.setDisplayOrder(1);
	_mainMenuButton.moveElementTo(kCreditsMainMenuLeft, kCreditsMainMenuTop);
	_mainMenuButton.startDisplaying();

	_largeSelect.initFromPICTFile("Images/Credits/SelectL.pict", true);
	_largeSelect.setDisplayOrder(2);
	_largeSelect.moveElementTo(kCreditsMainMenuSelectLeft, kCreditsMainMenuSelectTop);
	_largeSelect.startDisplaying();

	_smallSelect.initFromPICTFile("Images/Credits/SelectS.pict", true);
	_smallSelect.setDisplayOrder(2);
	_smallSelect.show();
	_smallSelect.startDisplaying();
	
	_menuSelection = -1;
	
	newMenuSelection(kCreditsMenuCoreTeam);
}

// Assumes the new selection is never more than one away from the old...
void CreditsMenu::newMenuSelection(const int newSelection) {
	if (newSelection != _menuSelection) {
		switch (newSelection) {
			case kCreditsMenuCoreTeam:
				_smallSelect.moveElementTo(kCoreTeamSelectLeft, kCoreTeamSelectTop);
				_creditsMovie.setTime(kCoreTeamTime);
				_creditsMovie.redrawMovieWorld();
				break;
			case kCreditsMenuSupportTeam:
				_smallSelect.moveElementTo(kSupportTeamSelectLeft, kSupportTeamSelectTop);
				_creditsMovie.setTime(kSupportTeamTime);
				_creditsMovie.redrawMovieWorld();
				break;
			case kCreditsMenuOriginalTeam:
				_smallSelect.moveElementTo(kOriginalTeamSelectLeft, kOriginalTeamSelectTop);
				_creditsMovie.setTime(kOriginalTeamTime);
				_creditsMovie.redrawMovieWorld();
				break;
			case kCreditsMenuTalent:
				_smallSelect.moveElementTo(kTalentSelectLeft, kTalentSelectTop);
				_creditsMovie.setTime(kTalentTime);
				_creditsMovie.redrawMovieWorld();
				break;
			case kCreditsMenuOtherTitles:
				_smallSelect.moveElementTo(kOtherTitlesSelectLeft, kOtherTitlesSelectTop);
				_smallSelect.show();
				_largeSelect.hide();
				_creditsMovie.setTime(kOtherTitlesTime);
				_creditsMovie.redrawMovieWorld();
				break;
			case kCreditsMenuMainMenu:
				_smallSelect.hide();
				_largeSelect.show();
				break;
		}

		_menuSelection = newSelection;
	}
}

void CreditsMenu::newMovieTime(const TimeValue newTime) {
	if (newTime < kSupportTeamTime) {
		_smallSelect.moveElementTo(kCoreTeamSelectLeft, kCoreTeamSelectTop);
		_menuSelection = kCreditsMenuCoreTeam;
	} else if (newTime < kOriginalTeamTime) {
		_smallSelect.moveElementTo(kSupportTeamSelectLeft, kSupportTeamSelectTop);
		_menuSelection = kCreditsMenuSupportTeam;
	} else if (newTime < kTalentTime) {
		_smallSelect.moveElementTo(kOriginalTeamSelectLeft, kOriginalTeamSelectTop);
		_menuSelection = kCreditsMenuOriginalTeam;
	} else if (newTime < kOtherTitlesTime) {
		_smallSelect.moveElementTo(kTalentSelectLeft, kTalentSelectTop);
		_smallSelect.show();
		_largeSelect.hide();
		_menuSelection = kCreditsMenuTalent;
	} else if ((int)newTime == -120) {
		// HACK: Avoid getting sent to the bottom button in the default case
		return;
	} else {
		_smallSelect.moveElementTo(kOtherTitlesSelectLeft, kOtherTitlesSelectTop);
		_smallSelect.show();
		_largeSelect.hide();
		_menuSelection = kCreditsMenuOtherTitles;
	}

	_creditsMovie.setTime(newTime);
	_creditsMovie.redrawMovieWorld();
}

void CreditsMenu::handleInput(const Input &input, const Hotspot *cursorSpot) {
	if (input.upButtonDown()) {
		if (_menuSelection > kCreditsFirstSelection)
			newMenuSelection(_menuSelection - 1);
	} else if (input.downButtonDown()) {
		if (_menuSelection < kCreditsLastSelection)
			newMenuSelection(_menuSelection + 1);
	} else if (input.leftButtonDown()) {
		newMovieTime(_creditsMovie.getTime() - kFrameIncrement);
	} else if (input.rightButtonDown()) {
		newMovieTime(_creditsMovie.getTime() + kFrameIncrement);
	} else if (JMPPPInput::isMenuButtonPressInput(input)) {
		if (_menuSelection == kCreditsMenuMainMenu) {
			_mainMenuButton.show();
			((PegasusEngine *)g_engine)->delayShell(kMenuButtonHiliteTime, kMenuButtonHiliteScale);
			_mainMenuButton.hide();
			setLastCommand(kMenuCmdCreditsMainMenu);
		}
	}

	InputHandler::handleInput(input, cursorSpot);
}

static const tCoordType kContinueLeft = 44;
static const tCoordType kContinueTop = 336;

static const tCoordType kContinueSelectLeft = 40;
static const tCoordType kContinueSelectTopDemo = 331;
static const tCoordType kContinueSelectTop = 332;

static const tCoordType kMainMenuLeftDemo = 44;
static const tCoordType kMainMenuTopDemo = 372;

static const tCoordType kMainMenuSelectLeftDemo = 40;
static const tCoordType kMainMenuSelectTopDemo = 367;

static const tCoordType kQuitLeftDemo = 32;
static const tCoordType kQuitTopDemo = 412;

static const tCoordType kQuitSelectLeftDemo = 28;
static const tCoordType kQuitSelectTopDemo = 408;

static const tCoordType kRestoreLeftDeath = 44;
static const tCoordType kRestoreTopDeath = 372;

static const tCoordType kRestoreSelectLeftDeath = 40;
static const tCoordType kRestoreSelectTopDeath = 368;

static const tCoordType kMainMenuLeft = 32;
static const tCoordType kMainMenuTop = 412;

static const tCoordType kMainMenuSelectLeft = 28;
static const tCoordType kMainMenuSelectTop = 408;

enum {
	kDeathScreenContinueDemo = 0,
	kDeathScreenMainMenuDemo,
	kDeathScreenQuitDemo,
	
	kFirstDeathSelectionDemo = kDeathScreenContinueDemo,
	kLastDeathSelectionDemo = kDeathScreenQuitDemo,

	kDeathScreenContinue = 0,
	kDeathScreenRestore,
	kDeathScreenMainMenu,
	
	kFirstDeathSelection = kDeathScreenContinue,
	kLastDeathSelection = kDeathScreenMainMenu
};

// Never set the current input handler to the DeathMenu.
DeathMenu::DeathMenu(const tDeathReason deathReason) : GameMenu(kDeathMenuID), _deathBackground(0), _continueButton(0),
		_mainMenuButton(0), _quitButton(0), _restoreButton(0), _largeSelect(0), _smallSelect(0) {
	PegasusEngine *vm = (PegasusEngine *)g_engine;
	bool isDemo = vm->isDemo();

	_playerWon = (deathReason == kPlayerWonGame);

	Common::String prefix = "Images/";
	Common::String imageName;
	if (isDemo) {
		prefix += "Demo/";
		imageName = prefix;

		switch (deathReason) {
		case kDeathFallOffCliff:
			imageName += "dPfall";
			break;
		case kDeathEatenByDinosaur:
			imageName += "dPdino";
			break;
		case kDeathStranded:
			imageName += "dPstuck";
			break;
		default:
			imageName += "dPdemowin";
			break;
		}

		imageName += ".pict";
	} else {
		prefix += "Death Screens/";
		imageName = prefix;

		static const char *fileNames[] = {
			"dAunmade", "dAbombed", "dAshot", "dAassass", "dAnuked",
			"dTunmade", "dTshot", "dPfall", "dPdino", "dPstuck",
			"dNchoke", "dNcaught", "dNcaught", "dNsub", "dNrobot1",
			"dNrobot2", "dMfall", "dMcaught", "dMtracks", "dMrobot",
			"dMtoast", "dMexplo1", "dMexplo2", "dMchoke1", "dMchoke2",
			"dMdroid", "dMfall", "dMgears", "dMshutt1", "dMshutt2",
			"dWpoison", "dWcaught", "dWplasma", "dWshot", "dAfinale"
		};

		imageName += fileNames[deathReason - 1];
		imageName += ".pict";
	}

	_deathBackground.initFromPICTFile(imageName);
	_deathReason = deathReason;

	if (!isDemo)
		drawAllScores();

	_deathBackground.setDisplayOrder(0);
	_deathBackground.startDisplaying();
	_deathBackground.show();

	if (isDemo) {
		if (_playerWon) // Make credits button...
			_continueButton.initFromPICTFile(prefix + "Credits.pict");
		else            // Make continue button...
			_continueButton.initFromPICTFile(prefix + "Continue.pict");

		_mainMenuButton.initFromPICTFile(prefix + "MainMenu.pict");
		_mainMenuButton.setDisplayOrder(1);
		_mainMenuButton.moveElementTo(kMainMenuLeftDemo, kMainMenuTopDemo);
		_mainMenuButton.startDisplaying();

		_quitButton.initFromPICTFile(prefix + "Quit.pict");
		_quitButton.setDisplayOrder(1);
		_quitButton.moveElementTo(kQuitLeftDemo, kQuitTopDemo);
		_quitButton.startDisplaying();

		_menuSelection = kDeathScreenContinueDemo;
	} else {
		if (!_playerWon) {
			_mainMenuButton.initFromPICTFile(prefix + "MainMenu.pict");
			_mainMenuButton.setDisplayOrder(1);
			_mainMenuButton.moveElementTo(kMainMenuLeft, kMainMenuTop);
			_mainMenuButton.startDisplaying();

			_restoreButton.initFromPICTFile(prefix + "Restore.pict");
			_restoreButton.setDisplayOrder(1);
			_restoreButton.moveElementTo(kRestoreLeftDeath, kRestoreTopDeath);
			_restoreButton.startDisplaying();
		}

		_continueButton.initFromPICTFile(prefix + "Continue.pict");

		_menuSelection = kDeathScreenContinue;
	}

	_smallSelect.initFromPICTFile(prefix + "SelectS.pict", true);
	_smallSelect.setDisplayOrder(2);
	_smallSelect.startDisplaying();

	_continueButton.setDisplayOrder(1);
	_continueButton.moveElementTo(kContinueLeft, kContinueTop);
	_continueButton.startDisplaying();

	if (isDemo || !_playerWon) {
		_largeSelect.initFromPICTFile(prefix + "SelectL.pict", true);
		_largeSelect.setDisplayOrder(2);
		_largeSelect.startDisplaying();
	} else {
		_triumphSound.initFromQuickTime("Sounds/Caldoria/Galactic Triumph");
		_triumphSound.playSound();
	}

	updateDisplay();
}

void DeathMenu::handleInput(const Input &input, const Hotspot *cursorSpot) {
	PegasusEngine *vm = (PegasusEngine *)g_engine;

	if (input.upButtonDown()) {
		if (_menuSelection > (vm->isDemo() ? kFirstDeathSelectionDemo : kFirstDeathSelection)) {
			_menuSelection--;
			updateDisplay();
		}
	} else if (input.downButtonDown() && (vm->isDemo() || !_playerWon)) {
		if (_menuSelection < (vm->isDemo() ? kLastDeathSelectionDemo : kLastDeathSelection)) {
			_menuSelection++;
			updateDisplay();
		}
	} else if (JMPPPInput::isMenuButtonPressInput(input)) {
		if (vm->isDemo()) {
			switch (_menuSelection) {
			case kDeathScreenContinueDemo:
				_continueButton.show();
				vm->delayShell(kMenuButtonHiliteTime, kMenuButtonHiliteScale);
				_continueButton.hide();
				setLastCommand(kMenuCmdDeathContinue);
				break;
			case kDeathScreenQuitDemo:
				_quitButton.show();
				vm->delayShell(kMenuButtonHiliteTime, kMenuButtonHiliteScale);
				_quitButton.hide();
				setLastCommand(kMenuCmdDeathQuitDemo);
				break;
			case kDeathScreenMainMenuDemo:
				_mainMenuButton.show();
				vm->delayShell(kMenuButtonHiliteTime, kMenuButtonHiliteScale);
				_mainMenuButton.hide();
				setLastCommand(kMenuCmdDeathMainMenuDemo);
				break;
			}
		} else {
			switch (_menuSelection) {
			case kDeathScreenContinue:
				_continueButton.show();
				vm->delayShell(kMenuButtonHiliteTime, kMenuButtonHiliteScale);
				_continueButton.hide();
				setLastCommand(kMenuCmdDeathContinue);
				break;
			case kDeathScreenRestore:
				_restoreButton.show();
				vm->delayShell(kMenuButtonHiliteTime, kMenuButtonHiliteScale);
				_restoreButton.hide();
				setLastCommand(kMenuCmdDeathRestore);
				break;
			case kDeathScreenMainMenu:
				_mainMenuButton.show();
				vm->delayShell(kMenuButtonHiliteTime, kMenuButtonHiliteScale);
				_mainMenuButton.hide();
				setLastCommand(kMenuCmdDeathMainMenu);
				break;
			}
		}
	}

	InputHandler::handleInput(input, cursorSpot);
}

void DeathMenu::updateDisplay() {
	if (((PegasusEngine *)g_engine)->isDemo()) {
		switch (_menuSelection) {
		case kDeathScreenContinueDemo:
			_smallSelect.moveElementTo(kContinueSelectLeft, kContinueSelectTopDemo);
			_smallSelect.show();
			_largeSelect.hide();
			break;
		case kDeathScreenQuitDemo:
			_largeSelect.moveElementTo(kQuitSelectLeftDemo, kQuitSelectTopDemo);
			_largeSelect.show();
			_smallSelect.hide();
			break;
		case kDeathScreenMainMenuDemo:
			_smallSelect.moveElementTo(kMainMenuSelectLeftDemo, kMainMenuSelectTopDemo);
			_smallSelect.show();
			_largeSelect.hide();
			break;
		}
	} else {
		switch (_menuSelection) {
		case kDeathScreenContinue:
			_smallSelect.moveElementTo(kContinueSelectLeft, kContinueSelectTop);
			_smallSelect.show();
			_largeSelect.hide();
			break;
		case kDeathScreenRestore:
			_smallSelect.moveElementTo(kRestoreSelectLeftDeath, kRestoreSelectTopDeath);
			_smallSelect.show();
			_largeSelect.hide();
			break;
		case kDeathScreenMainMenu:
			_largeSelect.moveElementTo(kMainMenuSelectLeft, kMainMenuSelectTop);
			_largeSelect.show();
			_smallSelect.hide();
			break;
		}
	}
}

void DeathMenu::drawAllScores() {
	Surface numbers;
	numbers.getImageFromPICTFile("Images/Death Screens/Numbers.pict");

	Common::Rect scoreBounds;
	tGameScoreType caldoriaTotal = 0;

	switch (_deathReason) {
	case kDeathCardBomb:
	case kDeathShotBySinclair:
	case kDeathSinclairShotDelegate:
	case kDeathNuclearExplosion:
	case kDeathGassedInNorad:
	case kDeathWokeUpNorad:
	case kDeathArrestedInNorad:
	case kDeathSubDestroyed:
	case kDeathRobotThroughNoradDoor:
	case kDeathRobotSubControlRoom:
	case kDeathWrongShuttleLock:
	case kDeathArrestedInMars:
	case kDeathRunOverByPod:
	case kDeathDidntGetOutOfWay:
	case kDeathReactorBurn:
	case kDeathDidntFindMarsBomb:
	case kDeathDidntDisarmMarsBomb:
	case kDeathNoMaskInMaze:
	case kDeathNoAirInMaze:
	case kDeathGroundByMazebot:
	case kDeathMissedOreBucket:
	case kDeathDidntLeaveBucket:
	case kDeathRanIntoCanyonWall:
	case kDeathRanIntoSpaceJunk:
	case kDeathDidntStopPoison:
	case kDeathArrestedInWSC:
	case kDeathHitByPlasma:
	case kDeathShotOnCatwalk:
	case kPlayerWonGame:
		caldoriaTotal += kMaxCaldoriaTSAScoreAfter;
		scoreBounds = Common::Rect(kDeathScreenScoreLeft, kDeathScreenScoreTop - kDeathScreenScoreSkipVert * 5,
				kDeathScreenScoreLeft + kDeathScreenScoreWidth, kDeathScreenScoreTop - kDeathScreenScoreSkipVert * 5 + kDeathScreenScoreHeight);
		drawScore(GameState.getGandhiScore(), kMaxGandhiScore, scoreBounds, &numbers);

		scoreBounds.translate(0, kDeathScreenScoreSkipVert);
		drawScore(GameState.getWSCScore(), kMaxWSCScore, scoreBounds, &numbers);

		scoreBounds.translate(0, kDeathScreenScoreSkipVert);
		drawScore(GameState.getNoradScore(), kMaxNoradScore, scoreBounds, &numbers);

		scoreBounds.translate(0, kDeathScreenScoreSkipVert);
		drawScore(GameState.getMarsScore(), kMaxMarsScore, scoreBounds, &numbers);
		// fall through
	case kDeathFallOffCliff:
	case kDeathEatenByDinosaur:
	case kDeathStranded:
	case kDeathShotByTSARobots:
		scoreBounds = Common::Rect(kDeathScreenScoreLeft, kDeathScreenScoreTop - kDeathScreenScoreSkipVert,
				kDeathScreenScoreLeft + kDeathScreenScoreWidth, kDeathScreenScoreTop - kDeathScreenScoreSkipVert + kDeathScreenScoreHeight);
		drawScore(GameState.getPrehistoricScore(), kMaxPrehistoricScore, scoreBounds, &numbers);
		// fall through
	case kDeathUncreatedInCaldoria:
	case kDeathUncreatedInTSA:
		scoreBounds = Common::Rect(kDeathScreenScoreLeft, kDeathScreenScoreTop, kDeathScreenScoreLeft + kDeathScreenScoreWidth,
				kDeathScreenScoreTop + kDeathScreenScoreHeight);
		caldoriaTotal += kMaxCaldoriaTSAScoreBefore;
		drawScore(GameState.getCaldoriaTSAScore(), caldoriaTotal, scoreBounds, &numbers);

		scoreBounds = Common::Rect(kDeathScreenScoreLeft, kDeathScreenScoreTop - kDeathScreenScoreSkipVert * 6,
				kDeathScreenScoreLeft + kDeathScreenScoreWidth, kDeathScreenScoreTop - kDeathScreenScoreSkipVert * 6 + kDeathScreenScoreHeight);

		drawScore(GameState.getTotalScore(), kMaxTotalScore, scoreBounds, &numbers);
		break;
	}
}

} // End of namespace Pegasus
