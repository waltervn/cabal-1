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

#include "create_kyradat.h"
#include "resources.h"

// Game tables

namespace {

const Game kyra1Games[] = {
	{ kKyra1, kPlatformDOS, kDemoVersion, EN_ANY },

	{ kKyra1, kPlatformDOS, kTalkieDemoVersion, EN_ANY },

	{ kKyra1, kPlatformAmiga, kNoSpecial, EN_ANY },
	{ kKyra1, kPlatformAmiga, kNoSpecial, DE_DEU },

	{ kKyra1, kPlatformDOS, kNoSpecial, EN_ANY },
	{ kKyra1, kPlatformDOS, kNoSpecial, DE_DEU },
	{ kKyra1, kPlatformDOS, kNoSpecial, FR_FRA },
	{ kKyra1, kPlatformDOS, kNoSpecial, IT_ITA },
	{ kKyra1, kPlatformDOS, kNoSpecial, ES_ESP },
	{ kKyra1, kPlatformDOS, kOldFloppy, RU_RUS },

	{ kKyra1, kPlatformDOS, kTalkieVersion, EN_ANY },
	{ kKyra1, kPlatformDOS, kTalkieVersion, DE_DEU },
	{ kKyra1, kPlatformDOS, kTalkieVersion, FR_FRA },
	{ kKyra1, kPlatformDOS, kTalkieVersion, IT_ITA },

	{ kKyra1, kPlatformFMTowns, kNoSpecial, EN_ANY },
	{ kKyra1, kPlatformFMTowns, kNoSpecial, JA_JPN },

	{ kKyra1, kPlatformPC98, kNoSpecial, JA_JPN },

	GAME_DUMMY_ENTRY
};

const Game kyra2Games[] = {
	{ kKyra2, kPlatformDOS, kDemoVersion, EN_ANY },

	{ kKyra2, kPlatformDOS, kTalkieDemoVersion, EN_ANY },
	{ kKyra2, kPlatformDOS, kTalkieDemoVersion, FR_FRA },
	{ kKyra2, kPlatformDOS, kTalkieDemoVersion, DE_DEU },

	{ kKyra2, kPlatformDOS, kNoSpecial, EN_ANY },
	{ kKyra2, kPlatformDOS, kNoSpecial, FR_FRA },
	{ kKyra2, kPlatformDOS, kNoSpecial, DE_DEU },
	{ kKyra2, kPlatformDOS, kNoSpecial, IT_ITA },
	{ kKyra2, kPlatformDOS, kNoSpecial, RU_RUS },

	{ kKyra2, kPlatformDOS, kTalkieVersion, EN_ANY },
	{ kKyra2, kPlatformDOS, kTalkieVersion, FR_FRA },
	{ kKyra2, kPlatformDOS, kTalkieVersion, DE_DEU },
	{ kKyra2, kPlatformDOS, kTalkieVersion, IT_ITA },
	{ kKyra2, kPlatformDOS, kTalkieVersion, RU_RUS },

	{ kKyra2, kPlatformFMTowns, kNoSpecial, EN_ANY },
	{ kKyra2, kPlatformFMTowns, kNoSpecial, JA_JPN },

	{ kKyra2, kPlatformPC98, kNoSpecial, EN_ANY },
	{ kKyra2, kPlatformPC98, kNoSpecial, JA_JPN },

	GAME_DUMMY_ENTRY
};

const Game kyra3Games[] = {
	{ kKyra3, kPlatformDOS, kTalkieVersion, EN_ANY },
	{ kKyra3, kPlatformDOS, kTalkieVersion, FR_FRA },
	{ kKyra3, kPlatformDOS, kTalkieVersion, DE_DEU },
	{ kKyra3, kPlatformDOS, kTalkieVersion, IT_ITA },
	{ kKyra3, kPlatformDOS, kTalkieVersion, ES_ESP },

	GAME_DUMMY_ENTRY
};

const Game eob1Games[] = {
	{ kEoB1, kPlatformDOS, kNoSpecial, EN_ANY },
	{ kEoB1, kPlatformDOS, kNoSpecial, DE_DEU },
	{ kEoB1, kPlatformDOS, kNoSpecial, IT_ITA },

	GAME_DUMMY_ENTRY
};

const Game eob2Games[] = {
	{ kEoB2, kPlatformDOS, kNoSpecial, EN_ANY },
	{ kEoB2, kPlatformDOS, kNoSpecial, DE_DEU },

	GAME_DUMMY_ENTRY
};

const Game lolGames[] = {
	{ kLoL, kPlatformDOS, kDemoVersion, EN_ANY },

	{ kLoL, kPlatformDOS, kNoSpecial, EN_ANY },
	{ kLoL, kPlatformDOS, kNoSpecial, RU_RUS },
	{ kLoL, kPlatformDOS, kNoSpecial, DE_DEU },
	{ kLoL, kPlatformDOS, kNoSpecial, FR_FRA },

	{ kLoL, kPlatformDOS, kTalkieVersion, EN_ANY },
	{ kLoL, kPlatformDOS, kTalkieVersion, FR_FRA },
	{ kLoL, kPlatformDOS, kTalkieVersion, DE_DEU },
	{ kLoL, kPlatformDOS, kTalkieVersion, IT_ITA },
	{ kLoL, kPlatformDOS, kTalkieVersion, RU_RUS },

	{ kLoL, kPlatformPC98, kNoSpecial, JA_JPN },

	{ kLoL, kPlatformFMTowns, kNoSpecial, JA_JPN },

	GAME_DUMMY_ENTRY
};

} // end of anonymous namespace

const Game * const gameDescs[] = {
	kyra1Games,
	kyra2Games,
	kyra3Games,
	lolGames,
	eob1Games,
	eob2Games,
	0
};

// Need tables

namespace {

const int kyra1FloppyNeed[] = {
	k1KallakWritingSeq,
	k1MalcolmTreeSeq,
	k1WestwoodLogoSeq,
	k1KyrandiaLogoSeq,
	k1KallakMalcolmSeq,
	k1ForestSeq,
	k1IntroCPSStrings,
	k1IntroCOLStrings,
	k1IntroWSAStrings,
	k1IntroStrings,
	k1RoomList,
	k1RoomFilenames,
	k1CharacterImageFilenames,
	k1DefaultShapes,
	k1ItemNames,
	k1TakenStrings,
	k1PlacedStrings,
	k1DroppedStrings,
	k1NoDropStrings,
	k1AmuleteAnimSeq,
	k1SpecialPalette1,
	k1SpecialPalette2,
	k1SpecialPalette3,
	k1SpecialPalette4,
	k1SpecialPalette5,
	k1SpecialPalette6,
	k1SpecialPalette7,
	k1SpecialPalette8,
	k1SpecialPalette9,
	k1SpecialPalette10,
	k1SpecialPalette11,
	k1SpecialPalette12,
	k1SpecialPalette13,
	k1SpecialPalette14,
	k1SpecialPalette15,
	k1SpecialPalette16,
	k1SpecialPalette17,
	k1SpecialPalette18,
	k1SpecialPalette19,
	k1SpecialPalette20,
	k1SpecialPalette21,
	k1SpecialPalette22,
	k1SpecialPalette23,
	k1SpecialPalette24,
	k1SpecialPalette25,
	k1SpecialPalette26,
	k1SpecialPalette27,
	k1SpecialPalette28,
	k1SpecialPalette29,
	k1SpecialPalette30,
	k1SpecialPalette31,
	k1SpecialPalette32,
	k1SpecialPalette33,
	k1PutDownString,
	k1WaitAmuletString,
	k1BlackJewelString,
	k1HealingTipString,
	k1PoisonGoneString,
	k1Healing1Shapes,
	k1Healing2Shapes,
	k1ThePoisonStrings,
	k1FluteStrings,
	k1PoisonDeathShapes,
	k1FluteShapes,
	k1Winter1Shapes,
	k1Winter2Shapes,
	k1Winter3Shapes,
	k1DrinkShapes,
	k1WispShapes,
	k1MagicAnimShapes,
	k1BranStoneShapes,
	k1WispJewelStrings,
	k1MagicJewelStrings,
	k1FlaskFullString,
	k1FullFlaskString,
	k1OutroReunionSeq,
	k1OutroHomeString,
	k1VeryCleverString,
	k1GUIStrings,
	k1NewGameString,
	k1ConfigStrings,
	k1AudioTracks,
	k1AudioTracks2,
	k1AudioTracksIntro,
	-1
};

const int kyra1FloppyOldNeed[] = {
	k1KallakWritingSeq,
	k1MalcolmTreeSeq,
	k1WestwoodLogoSeq,
	k1KyrandiaLogoSeq,
	k1KallakMalcolmSeq,
	k1ForestSeq,
	k1IntroCPSStrings,
	k1IntroCOLStrings,
	k1IntroWSAStrings,
	k1IntroStrings,
	k1RoomList,
	k1RoomFilenames,
	k1CharacterImageFilenames,
	k1DefaultShapes,
	k1ItemNames,
	k1TakenStrings,
	k1PlacedStrings,
	k1DroppedStrings,
	k1AmuleteAnimSeq,
	k1SpecialPalette1,
	k1SpecialPalette2,
	k1SpecialPalette3,
	k1SpecialPalette4,
	k1SpecialPalette5,
	k1SpecialPalette6,
	k1SpecialPalette7,
	k1SpecialPalette8,
	k1SpecialPalette9,
	k1SpecialPalette10,
	k1SpecialPalette11,
	k1SpecialPalette12,
	k1SpecialPalette13,
	k1SpecialPalette14,
	k1SpecialPalette15,
	k1SpecialPalette16,
	k1SpecialPalette17,
	k1SpecialPalette18,
	k1SpecialPalette19,
	k1SpecialPalette20,
	k1SpecialPalette21,
	k1SpecialPalette22,
	k1SpecialPalette23,
	k1SpecialPalette24,
	k1SpecialPalette25,
	k1SpecialPalette26,
	k1SpecialPalette27,
	k1SpecialPalette28,
	k1SpecialPalette29,
	k1SpecialPalette30,
	k1SpecialPalette31,
	k1SpecialPalette32,
	k1PutDownString,
	k1WaitAmuletString,
	k1BlackJewelString,
	k1HealingTipString,
	k1PoisonGoneString,
	k1Healing1Shapes,
	k1Healing2Shapes,
	k1ThePoisonStrings,
	k1FluteStrings,
	k1PoisonDeathShapes,
	k1FluteShapes,
	k1Winter1Shapes,
	k1Winter2Shapes,
	k1Winter3Shapes,
	k1DrinkShapes,
	k1WispShapes,
	k1MagicAnimShapes,
	k1BranStoneShapes,
	k1WispJewelStrings,
	k1MagicJewelStrings,
	k1FlaskFullString,
	k1FullFlaskString,
	k1OutroReunionSeq,
	k1OutroHomeString,
	k1VeryCleverString,
	k1GUIStrings,
	k1NewGameString,
	k1ConfigStrings,
	k1AudioTracks,
	k1AudioTracks2,
	k1AudioTracksIntro,
	-1
};

const int kyra1CDNeed[] = {
	k1KallakWritingSeq,
	k1MalcolmTreeSeq,
	k1WestwoodLogoSeq,
	k1KyrandiaLogoSeq,
	k1KallakMalcolmSeq,
	k1ForestSeq,
	k1IntroCPSStrings,
	k1IntroCOLStrings,
	k1IntroWSAStrings,
	k1IntroStrings,
	k1RoomList,
	k1RoomFilenames,
	k1CharacterImageFilenames,
	k1DefaultShapes,
	k1ItemNames,
	k1TakenStrings,
	k1PlacedStrings,
	k1DroppedStrings,
	k1NoDropStrings,
	k1AmuleteAnimSeq,
	k1SpecialPalette1,
	k1SpecialPalette2,
	k1SpecialPalette3,
	k1SpecialPalette4,
	k1SpecialPalette5,
	k1SpecialPalette6,
	k1SpecialPalette7,
	k1SpecialPalette8,
	k1SpecialPalette9,
	k1SpecialPalette10,
	k1SpecialPalette11,
	k1SpecialPalette12,
	k1SpecialPalette13,
	k1SpecialPalette14,
	k1SpecialPalette15,
	k1SpecialPalette16,
	k1SpecialPalette17,
	k1SpecialPalette18,
	k1SpecialPalette19,
	k1SpecialPalette20,
	k1SpecialPalette21,
	k1SpecialPalette22,
	k1SpecialPalette23,
	k1SpecialPalette24,
	k1SpecialPalette25,
	k1SpecialPalette26,
	k1SpecialPalette27,
	k1SpecialPalette28,
	k1SpecialPalette29,
	k1SpecialPalette30,
	k1SpecialPalette31,
	k1SpecialPalette32,
	k1SpecialPalette33,
	k1PutDownString,
	k1WaitAmuletString,
	k1BlackJewelString,
	k1HealingTipString,
	k1PoisonGoneString,
	k1Healing1Shapes,
	k1Healing2Shapes,
	k1ThePoisonStrings,
	k1FluteStrings,
	k1PoisonDeathShapes,
	k1FluteShapes,
	k1Winter1Shapes,
	k1Winter2Shapes,
	k1Winter3Shapes,
	k1DrinkShapes,
	k1WispShapes,
	k1MagicAnimShapes,
	k1BranStoneShapes,
	k1WispJewelStrings,
	k1MagicJewelStrings,
	k1FlaskFullString,
	k1FullFlaskString,
	k1OutroReunionSeq,
	k1OutroHomeString,
	k1VeryCleverString,
	k1GUIStrings,
	k1NewGameString,
	k1ConfigStrings,
	k1AudioTracks,
	k1AudioTracks2,
	k1AudioTracksIntro,
	-1
};

const int kyra1DemoNeed[] = {
	k1WestwoodLogoSeq,
	k1KyrandiaLogoSeq,
	k1IntroCPSStrings,
	k1IntroCOLStrings,
	k1IntroWSAStrings,
	k1IntroStrings,
	k1Demo1Seq,
	k1Demo2Seq,
	k1Demo3Seq,
	k1Demo4Seq,
	k1AudioTracksIntro,
	-1
};

const int kyra1DemoCDNeed[] = {
	k1KallakWritingSeq,
	k1MalcolmTreeSeq,
	k1WestwoodLogoSeq,
	k1KyrandiaLogoSeq,
	k1KallakMalcolmSeq,
	k1ForestSeq,
	k1IntroCPSStrings,
	k1IntroCOLStrings,
	k1IntroWSAStrings,
	k1IntroStrings,
	k1AudioTracksIntro,
	-1
};

const int kyra1TownsNeed[] = {
	k1KallakWritingSeq,
	k1MalcolmTreeSeq,
	k1WestwoodLogoSeq,
	k1KyrandiaLogoSeq,
	k1KallakMalcolmSeq,
	k1ForestSeq,
	k1IntroCPSStrings,
	k1IntroCOLStrings,
	k1IntroWSAStrings,
	k1IntroStrings,
	k1RoomList,
	k1RoomFilenames,
	k1CharacterImageFilenames,
	k1DefaultShapes,
	k1ItemNames,
	k1TakenStrings,
	k1PlacedStrings,
	k1DroppedStrings,
	k1NoDropStrings,
	k1AmuleteAnimSeq,
	k1SpecialPalette1,
	k1SpecialPalette2,
	k1SpecialPalette3,
	k1SpecialPalette4,
	k1SpecialPalette5,
	k1SpecialPalette6,
	k1SpecialPalette7,
	k1SpecialPalette8,
	k1SpecialPalette9,
	k1SpecialPalette10,
	k1SpecialPalette11,
	k1SpecialPalette12,
	k1SpecialPalette13,
	k1SpecialPalette14,
	k1SpecialPalette15,
	k1SpecialPalette16,
	k1SpecialPalette17,
	k1SpecialPalette18,
	k1SpecialPalette19,
	k1SpecialPalette20,
	k1SpecialPalette21,
	k1SpecialPalette22,
	k1SpecialPalette23,
	k1SpecialPalette24,
	k1SpecialPalette25,
	k1SpecialPalette26,
	k1SpecialPalette27,
	k1SpecialPalette28,
	k1SpecialPalette29,
	k1SpecialPalette30,
	k1SpecialPalette31,
	k1SpecialPalette32,
	k1SpecialPalette33,
	k1PutDownString,
	k1WaitAmuletString,
	k1BlackJewelString,
	k1HealingTipString,
	k1PoisonGoneString,
	k1Healing1Shapes,
	k1Healing2Shapes,
	k1ThePoisonStrings,
	k1FluteStrings,
	k1PoisonDeathShapes,
	k1FluteShapes,
	k1Winter1Shapes,
	k1Winter2Shapes,
	k1Winter3Shapes,
	k1DrinkShapes,
	k1WispShapes,
	k1MagicAnimShapes,
	k1BranStoneShapes,
	k1WispJewelStrings,
	k1MagicJewelStrings,
	k1FlaskFullString,
	k1FullFlaskString,
	k1OutroReunionSeq,
	k1OutroHomeString,
	k1VeryCleverString,
	k1GUIStrings,
	k1NewGameString,
	k1ConfigStrings,

	k1TownsMusicFadeTable,
	k1TownsSFXwdTable,
	k1TownsSFXbtTable,
	k1TownsCDATable,
	k1AudioTracks,
	k1CreditsStrings,
	-1
};

const int kyra1PC98Need[] = {
	k1KallakWritingSeq,
	k1MalcolmTreeSeq,
	k1WestwoodLogoSeq,
	k1KyrandiaLogoSeq,
	k1KallakMalcolmSeq,
	k1ForestSeq,
	k1IntroCPSStrings,
	k1IntroCOLStrings,
	k1IntroWSAStrings,
	k1IntroStrings,
	k1RoomList,
	k1RoomFilenames,
	k1CharacterImageFilenames,
	k1DefaultShapes,
	k1ItemNames,
	k1TakenStrings,
	k1PlacedStrings,
	k1DroppedStrings,
	k1NoDropStrings,
	k1AmuleteAnimSeq,
	k1SpecialPalette1,
	k1SpecialPalette2,
	k1SpecialPalette3,
	k1SpecialPalette4,
	k1SpecialPalette5,
	k1SpecialPalette6,
	k1SpecialPalette7,
	k1SpecialPalette8,
	k1SpecialPalette9,
	k1SpecialPalette10,
	k1SpecialPalette11,
	k1SpecialPalette12,
	k1SpecialPalette13,
	k1SpecialPalette14,
	k1SpecialPalette15,
	k1SpecialPalette16,
	k1SpecialPalette17,
	k1SpecialPalette18,
	k1SpecialPalette19,
	k1SpecialPalette20,
	k1SpecialPalette21,
	k1SpecialPalette22,
	k1SpecialPalette23,
	k1SpecialPalette24,
	k1SpecialPalette25,
	k1SpecialPalette26,
	k1SpecialPalette27,
	k1SpecialPalette28,
	k1SpecialPalette29,
	k1SpecialPalette30,
	k1SpecialPalette31,
	k1SpecialPalette32,
	k1SpecialPalette33,
	k1PutDownString,
	k1WaitAmuletString,
	k1BlackJewelString,
	k1HealingTipString,
	k1PoisonGoneString,
	k1Healing1Shapes,
	k1Healing2Shapes,
	k1ThePoisonStrings,
	k1FluteStrings,
	k1PoisonDeathShapes,
	k1FluteShapes,
	k1Winter1Shapes,
	k1Winter2Shapes,
	k1Winter3Shapes,
	k1DrinkShapes,
	k1WispShapes,
	k1MagicAnimShapes,
	k1BranStoneShapes,
	k1WispJewelStrings,
	k1MagicJewelStrings,
	k1FlaskFullString,
	k1FullFlaskString,
	k1OutroReunionSeq,
	k1OutroHomeString,
	k1VeryCleverString,
	k1GUIStrings,
	k1NewGameString,
	k1ConfigStrings,

	k1PC98StoryStrings,
	k1PC98IntroSfx,
	k1CreditsStrings,
	-1
};

const int kyra1AmigaNeed[] = {
	k1KallakWritingSeq,
	k1MalcolmTreeSeq,
	k1WestwoodLogoSeq,
	k1KyrandiaLogoSeq,
	k1KallakMalcolmSeq,
	k1ForestSeq,
	k1IntroCPSStrings,
	k1IntroWSAStrings,
	k1IntroCOLStrings,
	k1IntroStrings,
	k1RoomList,
	k1RoomFilenames,
	k1CharacterImageFilenames,
	k1DefaultShapes,
	k1ItemNames,
	k1TakenStrings,
	k1PlacedStrings,
	k1DroppedStrings,
	k1NoDropStrings,
	k1AmuleteAnimSeq,
	k1PutDownString,
	k1WaitAmuletString,
	k1BlackJewelString,
	k1HealingTipString,
	k1PoisonGoneString,
	k1Healing1Shapes,
	k1Healing2Shapes,
	k1ThePoisonStrings,
	k1FluteStrings,
	k1PoisonDeathShapes,
	k1FluteShapes,
	k1Winter1Shapes,
	k1Winter2Shapes,
	k1Winter3Shapes,
	k1DrinkShapes,
	k1WispShapes,
	k1MagicAnimShapes,
	k1BranStoneShapes,
	k1WispJewelStrings,
	k1MagicJewelStrings,
	k1FlaskFullString,
	k1FullFlaskString,
	k1OutroReunionSeq,
	k1OutroHomeString,
	k1VeryCleverString,
	k1GUIStrings,
	k1NewGameString,
	k1ConfigStrings,
	k1CreditsStrings,
	k1AmigaIntroSFXTable,
	k1AmigaGameSFXTable,
	-1
};

const int kyra2CDNeed[] = {
	k2SeqplayPakFiles,
	k2SeqplayCredits,
	k2SeqplayCreditsSpecial,
	k2SeqplayStrings,
	k2SeqplaySfxFiles,
	k2SeqplayTlkFiles,
	k2SeqplaySeqData,
	k2SeqplayIntroTracks,
	k2SeqplayFinaleTracks,
	k2IngameSfxFiles,
	k2IngameSfxIndex,
	k2IngameTracks,
	k2IngameTalkObjIndex,
	k2IngameShapeAnimData,
	-1
};

const int kyra2CDDemoNeed[] = {
	k2SeqplayPakFiles,
	k2SeqplayCredits,
	k2SeqplayCreditsSpecial,
	k2SeqplayStrings,
	k2SeqplaySfxFiles,
	k2SeqplayTlkFiles,
	k2SeqplaySeqData,
	k2SeqplayIntroTracks,
	k2SeqplayFinaleTracks,
	k2IngameSfxFiles,
	k2IngameSfxIndex,
	k2IngameTracks,
	k2IngameTalkObjIndex,
	k2IngameShapeAnimData,
	k2IngameTlkDemoStrings,
	-1
};

const int kyra2FloppyNeed[] = {
	k2SeqplayPakFiles,
	k2SeqplayStrings,
	k2SeqplaySfxFiles,
	k2SeqplayIntroTracks,
	k2SeqplayFinaleTracks,
	k2SeqplaySeqData,
	k2IngamePakFiles,
	k2IngameSfxFiles,
	k2IngameSfxIndex,
	k2IngameTracks,
	k2IngameTalkObjIndex,
	k2IngameShapeAnimData,
	-1
};

const int kyra2TownsNeed[] = {
	k2SeqplayPakFiles,
	k2SeqplayStrings,
	k2SeqplaySfxFiles,
	k2SeqplaySeqData,
	k2SeqplayIntroCDA,
	k2SeqplayFinaleCDA,
	k2IngamePakFiles,
	k2IngameSfxFiles,
	k2IngameSfxIndex,
	k2IngameCDA,
	k2IngameTalkObjIndex,
	k2IngameTimJpStrings,
	k2IngameShapeAnimData,
	-1
};

const int kyra2PC98Need[] = {
	k2SeqplayPakFiles,
	k2SeqplayStrings,
	k2SeqplaySfxFiles,
	k2SeqplaySeqData,
	k2IngamePakFiles,
	k2IngameSfxFiles,
	k2IngameSfxIndex,
	k2IngameTalkObjIndex,
	k2IngameTimJpStrings,
	k2IngameShapeAnimData,
	-1
};

const int kyra2DemoNeed[] = {
	k2SeqplayPakFiles,
	k2SeqplaySeqData,
	k2SeqplaySfxFiles,
	k2SeqplayIntroTracks,
	k2SeqplayShapeAnimData,
	-1
};

const int kyra3Need[] = {
	k3MainMenuStrings,
	k3MusicFiles,
	k3ScoreTable,
	k3SfxFiles,
	k3SfxMap,
	k3ItemAnimData,
	k3ItemMagicTable,
	k3ItemStringMap,
	-1
};

const int lolFloppyNeed[] = {
	kLoLIngamePakFiles,

	kLoLCharacterDefs,
	kLoLIngameSfxFiles,
	kLoLIngameSfxIndex,
	kLoLMusicTrackMap,
	kLoLIngameGMSfxIndex,
	kLoLIngameMT32SfxIndex,
	kLoLIngamePcSpkSfxIndex,
	kLoLSpellProperties,
	kLoLGameShapeMap,
	kLoLSceneItemOffs,
	kLoLCharInvIndex,
	kLoLCharInvDefs,
	kLoLCharDefsMan,
	kLoLCharDefsWoman,
	kLoLCharDefsKieran,
	kLoLCharDefsAkshel,
	kLoLExpRequirements,
	kLoLMonsterModifiers1,
	kLoLMonsterModifiers2,
	kLoLMonsterModifiers3,
	kLoLMonsterShiftOffsets,
	kLoLMonsterDirFlags,
	kLoLMonsterScaleY,
	kLoLMonsterScaleX,
	kLoLMonsterScaleWH,
	kLoLFlyingObjectShp,
	kLoLInventoryDesc,

	kLoLLevelShpList,
	kLoLLevelDatList,
	kLoLCompassDefs,
	kLoLStashSetup,
	kLoLDscWalls,
	kRpgCommonDscShapeIndex,
	kLoLDscOvlMap,
	kLoLDscScaleWidthData,
	kLoLDscScaleHeightData,
	kRpgCommonDscX,
	kLoLBaseDscY,
	kRpgCommonDscTileIndex,
	kRpgCommonDscUnk2,
	kRpgCommonDscDoorShapeIndex,
	kRpgCommonDscDimData1,
	kRpgCommonDscDimData2,
	kRpgCommonDscBlockMap,
	kRpgCommonDscDimMap,
	kLoLDscOvlIndex,
	kRpgCommonDscBlockIndex,
	kRpgCommonDscDoorY2,
	kRpgCommonDscDoorFrameY1,
	kRpgCommonDscDoorFrameY2,
	kLoLDscDoorScale,
	kLoLDscDoor4,
	kLoLDscDoorX,
	kLoLDscDoorY,

	kLoLScrollXTop,
	kLoLScrollYTop,
	kLoLScrollXBottom,
	kLoLScrollYBottom,

	kLoLButtonDefs,
	kLoLButtonList1,
	kLoLButtonList2,
	kLoLButtonList3,
	kLoLButtonList4,
	kLoLButtonList5,
	kLoLButtonList6,
	kLoLButtonList7,
	kLoLButtonList8,

	kLoLLegendData,
	kLoLMapCursorOvl,
	kLoLMapStringId,

	kLoLSpellbookAnim,
	kLoLSpellbookCoords,
	kLoLHealShapeFrames,
	kLoLLightningDefs,
	kLoLFireballCoords,

	-1
};

const int lolPC98Need[] = {
	kLoLIngamePakFiles,

	kLoLCharacterDefs,
	kLoLIngameSfxFiles,
	kLoLIngameSfxIndex,
	kLoLSpellProperties,
	kLoLGameShapeMap,
	kLoLSceneItemOffs,
	kLoLCharInvIndex,
	kLoLCharInvDefs,
	kLoLCharDefsMan,
	kLoLCharDefsWoman,
	kLoLCharDefsKieran,
	kLoLCharDefsAkshel,
	kLoLExpRequirements,
	kLoLMonsterModifiers1,
	kLoLMonsterModifiers2,
	kLoLMonsterModifiers3,
	kLoLMonsterShiftOffsets,
	kLoLMonsterDirFlags,
	kLoLMonsterScaleY,
	kLoLMonsterScaleX,
	kLoLMonsterScaleWH,
	kLoLFlyingObjectShp,
	kLoLInventoryDesc,

	kLoLLevelShpList,
	kLoLLevelDatList,
	kLoLCompassDefs,
	kLoLStashSetup,
	kLoLDscWalls,
	kRpgCommonDscShapeIndex,
	kLoLDscOvlMap,
	kLoLDscScaleWidthData,
	kLoLDscScaleHeightData,
	kRpgCommonDscX,
	kLoLBaseDscY,
	kRpgCommonDscTileIndex,
	kRpgCommonDscUnk2,
	kRpgCommonDscDoorShapeIndex,
	kRpgCommonDscDimData1,
	kRpgCommonDscDimData2,
	kRpgCommonDscBlockMap,
	kRpgCommonDscDimMap,
	kLoLDscOvlIndex,
	kRpgCommonDscBlockIndex,
	kRpgCommonDscDoorY2,
	kRpgCommonDscDoorFrameY1,
	kRpgCommonDscDoorFrameY2,
	kLoLDscDoorScale,
	kLoLDscDoor4,
	kLoLDscDoorX,
	kLoLDscDoorY,

	kLoLScrollXTop,
	kLoLScrollYTop,
	kLoLScrollXBottom,
	kLoLScrollYBottom,

	kLoLButtonDefs,
	kLoLButtonList1,
	kLoLButtonList2,
	kLoLButtonList3,
	kLoLButtonList4,
	kLoLButtonList5,
	kLoLButtonList6,
	kLoLButtonList7,
	kLoLButtonList8,

	kLoLLegendData,
	kLoLMapStringId,

	kLoLSpellbookAnim,
	kLoLSpellbookCoords,
	kLoLHealShapeFrames,
	kLoLLightningDefs,
	kLoLFireballCoords,

	kLoLCredits,

	-1
};

const int lolFMTownsNeed[] = {
	kLoLIngamePakFiles,

	kLoLCharacterDefs,
	kLoLIngameSfxFiles,
	kLoLIngameSfxIndex,
	kLoLSpellProperties,
	kLoLGameShapeMap,
	kLoLSceneItemOffs,
	kLoLCharInvIndex,
	kLoLCharInvDefs,
	kLoLCharDefsMan,
	kLoLCharDefsWoman,
	kLoLCharDefsKieran,
	kLoLCharDefsAkshel,
	kLoLExpRequirements,
	kLoLMonsterModifiers1,
	kLoLMonsterModifiers2,
	kLoLMonsterModifiers3,
	kLoLMonsterShiftOffsets,
	kLoLMonsterDirFlags,
	kLoLMonsterScaleY,
	kLoLMonsterScaleX,
	kLoLMonsterScaleWH,
	kLoLFlyingObjectShp,
	kLoLInventoryDesc,

	kLoLLevelShpList,
	kLoLLevelDatList,
	kLoLCompassDefs,
	kLoLStashSetup,
	kLoLDscWalls,
	kRpgCommonDscShapeIndex,
	kLoLDscOvlMap,
	kLoLDscScaleWidthData,
	kLoLDscScaleHeightData,
	kRpgCommonDscX,
	kLoLBaseDscY,
	kRpgCommonDscTileIndex,
	kRpgCommonDscUnk2,
	kRpgCommonDscDoorShapeIndex,
	kRpgCommonDscDimData1,
	kRpgCommonDscDimData2,
	kRpgCommonDscBlockMap,
	kRpgCommonDscDimMap,
	kLoLDscOvlIndex,
	kRpgCommonDscBlockIndex,
	kRpgCommonDscDoorY2,
	kRpgCommonDscDoorFrameY1,
	kRpgCommonDscDoorFrameY2,
	kLoLDscDoorScale,
	kLoLDscDoor4,
	kLoLDscDoorX,
	kLoLDscDoorY,

	kLoLScrollXTop,
	kLoLScrollYTop,
	kLoLScrollXBottom,
	kLoLScrollYBottom,

	kLoLButtonDefs,
	kLoLButtonList1,
	kLoLButtonList2,
	kLoLButtonList3,
	kLoLButtonList4,
	kLoLButtonList5,
	kLoLButtonList6,
	kLoLButtonList7,
	kLoLButtonList8,

	kLoLLegendData,
	kLoLMapStringId,

	kLoLSpellbookAnim,
	kLoLSpellbookCoords,
	kLoLHealShapeFrames,
	kLoLLightningDefs,
	kLoLFireballCoords,

	kLoLCredits,

	-1
};

const int lolCDNeed[] = {
	kLoLHistory,
	kLoLCharacterDefs,
	kLoLIngameSfxFiles,
	kLoLIngameSfxIndex,
	kLoLMusicTrackMap,
	kLoLIngameGMSfxIndex,
	kLoLIngameMT32SfxIndex,
	kLoLIngamePcSpkSfxIndex,
	kLoLSpellProperties,
	kLoLGameShapeMap,
	kLoLSceneItemOffs,
	kLoLCharInvIndex,
	kLoLCharInvDefs,
	kLoLCharDefsMan,
	kLoLCharDefsWoman,
	kLoLCharDefsKieran,
	kLoLCharDefsAkshel,
	kLoLExpRequirements,
	kLoLMonsterModifiers1,
	kLoLMonsterModifiers2,
	kLoLMonsterModifiers3,
	kLoLMonsterModifiers4,
	kLoLMonsterShiftOffsets,
	kLoLMonsterDirFlags,
	kLoLMonsterScaleY,
	kLoLMonsterScaleX,
	kLoLMonsterScaleWH,
	kLoLFlyingObjectShp,
	kLoLInventoryDesc,

	kLoLLevelShpList,
	kLoLLevelDatList,
	kLoLCompassDefs,
	kLoLItemPrices,
	kLoLStashSetup,
	kLoLDscWalls,
	kRpgCommonDscShapeIndex,
	kLoLDscOvlMap,
	kLoLDscScaleWidthData,
	kLoLDscScaleHeightData,
	kRpgCommonDscX,
	kLoLBaseDscY,
	kRpgCommonDscTileIndex,
	kRpgCommonDscUnk2,
	kRpgCommonDscDoorShapeIndex,
	kRpgCommonDscDimData1,
	kRpgCommonDscDimData2,
	kRpgCommonDscBlockMap,
	kRpgCommonDscDimMap,
	kLoLDscOvlIndex,
	kRpgCommonDscBlockIndex,
	kRpgCommonDscDoorY2,
	kRpgCommonDscDoorFrameY1,
	kRpgCommonDscDoorFrameY2,
	kLoLDscDoorScale,
	kLoLDscDoor4,
	kLoLDscDoorX,
	kLoLDscDoorY,

	kLoLScrollXTop,
	kLoLScrollYTop,
	kLoLScrollXBottom,
	kLoLScrollYBottom,

	kLoLButtonDefs,
	kLoLButtonList1,
	kLoLButtonList2,
	kLoLButtonList3,
	kLoLButtonList4,
	kLoLButtonList5,
	kLoLButtonList6,
	kLoLButtonList7,
	kLoLButtonList8,

	kLoLLegendData,
	kLoLMapCursorOvl,
	kLoLMapStringId,

	kLoLSpellbookAnim,
	kLoLSpellbookCoords,
	kLoLHealShapeFrames,
	kLoLLightningDefs,
	kLoLFireballCoords,
	-1
};

const int lolDemoNeed[] = {
	k2SeqplayPakFiles,
	k2SeqplayStrings,
	k2SeqplaySeqData,
	k2SeqplaySfxFiles,
	k2SeqplayIntroTracks,
	-1
};

const int eob1FloppyNeed[] = {
	kEoBBaseChargenStrings1,
	kEoBBaseChargenStrings2,
	kEoBBaseChargenStartLevels,
	kEoBBaseChargenStatStrings,
	kEoBBaseChargenRaceSexStrings,
	kEoBBaseChargenClassStrings,
	kEoBBaseChargenAlignmentStrings,
	kEoBBaseChargenEnterGameStrings,
	kEoBBaseChargenClassMinStats,
	kEoBBaseChargenRaceMinStats,
	kEoBBaseChargenRaceMaxStats,

	kEoBBaseSaveThrowTable1,
	kEoBBaseSaveThrowTable2,
	kEoBBaseSaveThrowTable3,
	kEoBBaseSaveThrowTable4,
	kEoBBaseSaveThrwLvlIndex,
	kEoBBaseSaveThrwModDiv,
	kEoBBaseSaveThrwModExt,

	kEoB1MainMenuStrings,
	kEoB1BonusStrings,

	kEoB1IntroFilesOpening,
	kEoB1IntroFilesTower,
	kEoB1IntroFilesOrb,
	kEoB1IntroFilesWdEntry,
	kEoB1IntroFilesKing,
	kEoB1IntroFilesHands,
	kEoB1IntroFilesWdExit,
	kEoB1IntroFilesTunnel,
	kEoB1IntroOpeningFrmDelay,
	kEoB1IntroWdEncodeX,
	kEoB1IntroWdEncodeY,
	kEoB1IntroWdEncodeWH,
	kEoB1IntroWdDsX,
	kEoB1IntroWdDsY,
	kEoB1IntroTvlX1,
	kEoB1IntroTvlY1,
	kEoB1IntroTvlX2,
	kEoB1IntroTvlY2,
	kEoB1IntroTvlW,
	kEoB1IntroTvlH,

	kEoB1DoorShapeDefs,
	kEoB1DoorSwitchShapeDefs,
	kEoB1DoorSwitchCoords,
	kEoB1MonsterProperties,
	kEoB1EnemyMageSpellList,
	kEoB1EnemyMageSfx,
	kEoB1BeholderSpellList,
	kEoB1BeholderSfx,
	kEoB1TurnUndeadString,

	kEoB1CgaMappingDefault,
	kEoB1CgaMappingAlt,
	kEoB1CgaMappingInv,
	kEoB1CgaMappingItemsL,
	kEoB1CgaMappingItemsS,
	kEoB1CgaMappingThrown,
	kEoB1CgaMappingIcons,
	kEoB1CgaMappingDeco,
	kEoB1CgaLevelMappingIndex,
	kEoB1CgaMappingLevel0,
	kEoB1CgaMappingLevel1,
	kEoB1CgaMappingLevel2,
	kEoB1CgaMappingLevel3,
	kEoB1CgaMappingLevel4,

	kEoB1NpcShpData,
	kEoB1NpcSubShpIndex1,
	kEoB1NpcSubShpIndex2,
	kEoB1NpcSubShpY,
	kEoB1Npc0Strings,
	kEoB1Npc11Strings,
	kEoB1Npc12Strings,
	kEoB1Npc21Strings,
	kEoB1Npc22Strings,
	kEoB1Npc31Strings,
	kEoB1Npc32Strings,
	kEoB1Npc4Strings,
	kEoB1Npc5Strings,
	kEoB1Npc6Strings,
	kEoB1Npc7Strings,

	kEoBBasePryDoorStrings,
	kEoBBaseWarningStrings,

	kEoBBaseItemSuffixStringsRings,
	kEoBBaseItemSuffixStringsPotions,
	kEoBBaseItemSuffixStringsWands,

	kEoBBaseRipItemStrings,
	kEoBBaseCursedString,
	kEoBBaseEnchantedString,
	kEoBBaseMagicObjectStrings,
	kEoBBaseMagicObjectString5,
	kEoBBasePatternSuffix,
	kEoBBasePatternGrFix1,
	kEoBBasePatternGrFix2,
	kEoBBaseValidateArmorString,
	kEoBBaseValidateNoDropString,
	kEoBBasePotionStrings,
	kEoBBaseWandStrings,
	kEoBBaseItemMisuseStrings,

	kEoBBaseTakenStrings,
	kEoBBasePotionEffectStrings,

	kEoBBaseYesNoStrings,
	kRpgCommonMoreStrings,
	kEoBBaseNpcMaxStrings,
	kEoBBaseNpcJoinStrings,
	kEoBBaseCancelStrings,

	kEoBBaseMenuStringsMain,
	kEoBBaseMenuStringsSaveLoad,
	kEoBBaseMenuStringsOnOff,
	kEoBBaseMenuStringsSpells,
	kEoBBaseMenuStringsRest,
	kEoBBaseMenuStringsDrop,
	kEoBBaseMenuStringsExit,
	kEoBBaseMenuStringsStarve,
	kEoBBaseMenuStringsScribe,
	kEoBBaseMenuStringsDrop2,
	kEoBBaseMenuStringsHead,
	kEoBBaseMenuStringsPoison,
	kEoBBaseMenuStringsMgc,
	kEoBBaseMenuStringsPrefs,
	kEoBBaseMenuStringsRest2,
	kEoBBaseMenuStringsRest4,
	kEoBBaseMenuStringsDefeat,
	kEoBBaseMenuYesNoStrings,

	kEoBBaseSpellLevelsMage,
	kEoBBaseSpellLevelsCleric,
	kEoBBaseNumSpellsCleric,
	kEoBBaseNumSpellsWisAdj,
	kEoBBaseNumSpellsPal,
	kEoBBaseNumSpellsMage,

	kEoBBaseCharGuiStringsHp,
	kEoBBaseCharGuiStringsWp1,
	kEoBBaseCharGuiStringsWr,
	kEoBBaseCharGuiStringsSt1,
	kEoBBaseCharGuiStringsIn,

	kEoBBaseCharStatusStrings7,
	kEoBBaseCharStatusStrings81,
	kEoBBaseCharStatusStrings9,
	kEoBBaseCharStatusStrings131,

	kEoBBaseLevelGainStrings,
	kEoBBaseExperienceTable0,
	kEoBBaseExperienceTable1,
	kEoBBaseExperienceTable2,
	kEoBBaseExperienceTable3,
	kEoBBaseExperienceTable4,

	kEoBBaseBookNumbers,
	kEoBBaseMageSpellsList,
	kEoBBaseClericSpellsList,
	kEoBBaseSpellNames,
	kEoBBaseMagicStrings1,
	kEoBBaseMagicStrings2,
	kEoBBaseMagicStrings3,
	kEoBBaseMagicStrings4,
	kEoBBaseMagicStrings6,
	kEoBBaseMagicStrings7,
	kEoBBaseMagicStrings8,

	kEoBBaseExpObjectTblIndex,
	kEoBBaseExpObjectShpStart,
	kEoBBaseExpObjectTbl1,
	kEoBBaseExpObjectTbl2,
	kEoBBaseExpObjectTbl3,
	kEoBBaseExpObjectY,

	kEoBBaseSparkDefSteps,
	kEoBBaseSparkDefSubSteps,
	kEoBBaseSparkDefShift,
	kEoBBaseSparkDefAdd,
	kEoBBaseSparkDefX,
	kEoBBaseSparkDefY,
	kEoBBaseSparkOfFlags1,
	kEoBBaseSparkOfFlags2,
	kEoBBaseSparkOfShift,
	kEoBBaseSparkOfX,
	kEoBBaseSparkOfY,

	kEoBBaseSpellProperties,
	kEoBBaseMagicFlightProps,
	kEoBBaseTurnUndeadEffect,
	kEoBBaseBurningHandsDest,
	kEoBBaseConeOfColdDest1,
	kEoBBaseConeOfColdDest2,
	kEoBBaseConeOfColdDest3,
	kEoBBaseConeOfColdDest4,
	kEoBBaseConeOfColdGfxTbl,

	kRpgCommonDscDoorShapeIndex,
	kEoBBaseWllFlagPreset,
	kEoBBaseDscShapeCoords,
	kEoBBaseDscDoorScaleOffs,
	kEoBBaseDscDoorScaleMult1,
	kEoBBaseDscDoorScaleMult2,
	kEoBBaseDscDoorScaleMult3,
	kEoBBaseDscDoorScaleMult4,
	kEoBBaseDscDoorScaleMult5,
	kEoBBaseDscDoorScaleMult6,
	kEoBBaseDscDoorXE,
	kEoBBaseDscDoorY1,
	kEoBBaseDscDoorY3,
	kEoBBaseDscDoorY4,
	kEoBBaseDscDoorY5,
	kEoBBaseDscDoorY6,
	kEoBBaseDscDoorY7,
	kEoBBaseDscDoorCoordsExt,
	kRpgCommonDscDoorFrameY1,
	kRpgCommonDscDoorFrameY2,
	kRpgCommonDscDoorFrameIndex1,
	kRpgCommonDscDoorFrameIndex2,

	kEoBBaseDscItemPosIndex,
	kEoBBaseDscItemShpX,
	kEoBBaseDscItemScaleIndex,
	kEoBBaseDscItemTileIndex,
	kEoBBaseDscItemShapeMap,
	kEoBBaseDscTelptrShpCoords,

	kEoBBasePortalSeqData,
	kEoBBaseManDef,
	kEoBBaseManWord,
	kEoBBaseManPrompt,

	kEoBBaseDscMonsterFrmOffsTbl1,
	kEoBBaseDscMonsterFrmOffsTbl2,

	kEoBBaseInvSlotX,
	kEoBBaseInvSlotY,
	kEoBBaseSlotValidationFlags,

	kEoBBaseProjectileWeaponTypes,
	kEoBBaseWandTypes,

	kEoBBaseDrawObjPosIndex,
	kEoBBaseFlightObjFlipIndex,
	kEoBBaseFlightObjShpMap,
	kEoBBaseFlightObjSclIndex,

	kRpgCommonDscShapeIndex,
	kRpgCommonDscX,
	kRpgCommonDscTileIndex,
	kRpgCommonDscUnk2,
	kRpgCommonDscDimData1,
	kRpgCommonDscDimData2,
	kRpgCommonDscBlockMap,
	kRpgCommonDscDimMap,
	kRpgCommonDscBlockIndex,

	kEoBBaseClassModifierFlags,

	kEoBBaseMonsterStepTable01,
	//kEoBBaseMonsterStepTable1,
	kEoBBaseMonsterStepTable2,
	kEoBBaseMonsterStepTable3,
	kEoBBaseMonsterCloseAttPosTable1,
	kEoBBaseMonsterCloseAttPosTable21,
	//kEoBBaseMonsterCloseAttUnkTable,
	kEoBBaseMonsterCloseAttChkTable1,
	kEoBBaseMonsterCloseAttChkTable2,
	kEoBBaseMonsterCloseAttDstTable1,
	kEoBBaseMonsterCloseAttDstTable2,

	kEoBBaseMonsterProximityTable,
	kEoBBaseFindBlockMonstersTable,
	kEoBBaseMonsterDirChangeTable,
	kEoBBaseMonsterDistAttStrings,
	kEoBBaseEncodeMonsterDefs,
	kEoBBaseNpcPresets,
	//kEoB1Npc1Strings,
	//kEoB1Npc2Strings,
	-1
};

const int eob2FloppyNeed[] = {
	kEoBBaseChargenStrings1,
	kEoBBaseChargenStrings2,
	kEoBBaseChargenStartLevels,
	kEoBBaseChargenStatStrings,
	kEoBBaseChargenRaceSexStrings,
	kEoBBaseChargenClassStrings,
	kEoBBaseChargenAlignmentStrings,
	kEoBBaseChargenEnterGameStrings,
	kEoBBaseChargenClassMinStats,
	kEoBBaseChargenRaceMinStats,
	kEoBBaseChargenRaceMaxStats,

	kEoBBaseSaveThrowTable1,
	kEoBBaseSaveThrowTable2,
	kEoBBaseSaveThrowTable3,
	kEoBBaseSaveThrowTable4,
	kEoBBaseSaveThrwLvlIndex,
	kEoBBaseSaveThrwModDiv,
	kEoBBaseSaveThrwModExt,

	kEoBBasePryDoorStrings,
	kEoBBaseWarningStrings,

	kEoBBaseItemSuffixStringsRings,
	kEoBBaseItemSuffixStringsPotions,
	kEoBBaseItemSuffixStringsWands,

	kEoBBaseRipItemStrings,
	kEoBBaseCursedString,
	kEoBBaseEnchantedString,
	kEoBBaseMagicObjectStrings,
	kEoBBaseMagicObjectString5,
	kEoBBasePatternSuffix,
	kEoBBasePatternGrFix1,
	kEoBBasePatternGrFix2,
	kEoBBaseValidateArmorString,
	kEoBBaseValidateCursedString,
	kEoBBaseValidateNoDropString,
	kEoBBasePotionStrings,
	kEoBBaseWandStrings,
	kEoBBaseItemMisuseStrings,

	kEoBBaseTakenStrings,
	kEoBBasePotionEffectStrings,

	kEoBBaseYesNoStrings,
	kRpgCommonMoreStrings,
	kEoBBaseNpcMaxStrings,
	kEoBBaseOkStrings,
	kEoBBaseNpcJoinStrings,
	kEoBBaseCancelStrings,
	kEoBBaseAbortStrings,

	kEoBBaseMenuStringsMain,
	kEoBBaseMenuStringsSaveLoad,
	kEoBBaseMenuStringsOnOff,
	kEoBBaseMenuStringsSpells,
	kEoBBaseMenuStringsRest,
	kEoBBaseMenuStringsDrop,
	kEoBBaseMenuStringsExit,
	kEoBBaseMenuStringsStarve,
	kEoBBaseMenuStringsScribe,
	kEoBBaseMenuStringsDrop2,
	kEoBBaseMenuStringsHead,
	kEoBBaseMenuStringsPoison,
	kEoBBaseMenuStringsMgc,
	kEoBBaseMenuStringsPrefs,
	kEoBBaseMenuStringsRest2,
	kEoBBaseMenuStringsRest3,
	kEoBBaseMenuStringsRest4,
	kEoBBaseMenuStringsDefeat,
	kEoBBaseMenuStringsTransfer,
	kEoBBaseMenuStringsSpec,
	kEoBBaseMenuStringsSpellNo,
	kEoBBaseMenuYesNoStrings,

	kEoBBaseSpellLevelsMage,
	kEoBBaseSpellLevelsCleric,
	kEoBBaseNumSpellsCleric,
	kEoBBaseNumSpellsWisAdj,
	kEoBBaseNumSpellsPal,
	kEoBBaseNumSpellsMage,

	kEoBBaseCharGuiStringsHp,
	kEoBBaseCharGuiStringsWp2,
	kEoBBaseCharGuiStringsWr,
	kEoBBaseCharGuiStringsSt2,
	kEoBBaseCharGuiStringsIn,

	kEoBBaseCharStatusStrings7,
	kEoBBaseCharStatusStrings82,
	kEoBBaseCharStatusStrings9,
	kEoBBaseCharStatusStrings12,
	kEoBBaseCharStatusStrings132,

	kEoBBaseLevelGainStrings,
	kEoBBaseExperienceTable0,
	kEoBBaseExperienceTable1,
	kEoBBaseExperienceTable2,
	kEoBBaseExperienceTable3,
	kEoBBaseExperienceTable4,

	kEoBBaseBookNumbers,
	kEoBBaseMageSpellsList,
	kEoBBaseClericSpellsList,
	kEoBBaseSpellNames,
	kEoBBaseMagicStrings1,
	kEoBBaseMagicStrings2,
	kEoBBaseMagicStrings3,
	kEoBBaseMagicStrings4,
	kEoBBaseMagicStrings6,
	kEoBBaseMagicStrings7,
	kEoBBaseMagicStrings8,

	kEoBBaseExpObjectTlMode,
	kEoBBaseExpObjectTblIndex,
	kEoBBaseExpObjectShpStart,
	kEoBBaseExpObjectTbl1,
	kEoBBaseExpObjectTbl2,
	kEoBBaseExpObjectTbl3,
	kEoBBaseExpObjectY,

	kEoBBaseSparkDefSteps,
	kEoBBaseSparkDefSubSteps,
	kEoBBaseSparkDefShift,
	kEoBBaseSparkDefAdd,
	kEoBBaseSparkDefX,
	kEoBBaseSparkDefY,
	kEoBBaseSparkOfFlags1,
	kEoBBaseSparkOfFlags2,
	kEoBBaseSparkOfShift,
	kEoBBaseSparkOfX,
	kEoBBaseSparkOfY,

	kEoBBaseSpellProperties,
	kEoBBaseMagicFlightProps,
	kEoBBaseTurnUndeadEffect,
	kEoBBaseBurningHandsDest,
	kEoBBaseConeOfColdDest1,
	kEoBBaseConeOfColdDest2,
	kEoBBaseConeOfColdDest3,
	kEoBBaseConeOfColdDest4,
	kEoBBaseConeOfColdGfxTbl,

	kRpgCommonDscDoorShapeIndex,
	kEoBBaseWllFlagPreset,
	kEoBBaseDscShapeCoords,

	kEoBBaseDscDoorScaleOffs,
	kEoBBaseDscDoorScaleMult1,
	kEoBBaseDscDoorScaleMult2,
	kEoBBaseDscDoorScaleMult3,
	kEoBBaseDscDoorType5Offs,
	kEoBBaseDscDoorY1,
	kRpgCommonDscDoorY2,
	kRpgCommonDscDoorFrameY1,
	kRpgCommonDscDoorFrameY2,

	kEoBBaseDscItemPosIndex,
	kEoBBaseDscItemShpX,
	kEoBBaseDscItemScaleIndex,
	kEoBBaseDscItemTileIndex,
	kEoBBaseDscItemShapeMap,
	kEoBBaseDscTelptrShpCoords,

	kEoBBasePortalSeqData,
	kEoBBaseManDef,
	kEoBBaseManWord,
	kEoBBaseManPrompt,

	kEoBBaseDscMonsterFrmOffsTbl1,
	kEoBBaseDscMonsterFrmOffsTbl2,

	kEoBBaseInvSlotX,
	kEoBBaseInvSlotY,
	kEoBBaseSlotValidationFlags,

	kEoBBaseProjectileWeaponTypes,
	kEoBBaseWandTypes,

	kEoBBaseDrawObjPosIndex,
	kEoBBaseFlightObjFlipIndex,
	kEoBBaseFlightObjShpMap,
	kEoBBaseFlightObjSclIndex,

	kEoB2MainMenuStrings,

	kEoB2TransferPortraitFrames,
	kEoB2TransferConvertTable,
	kEoB2TransferItemTable,
	kEoB2TransferExpTable,
	kEoB2TransferStrings1,
	kEoB2TransferStrings2,
	kEoB2TransferLabels,

	kEoB2IntroStrings,
	kEoB2IntroCPSFiles,
	kEoB2IntroAnimData00,
	kEoB2IntroAnimData01,
	kEoB2IntroAnimData02,
	kEoB2IntroAnimData03,
	kEoB2IntroAnimData04,
	kEoB2IntroAnimData05,
	kEoB2IntroAnimData06,
	kEoB2IntroAnimData07,
	kEoB2IntroAnimData08,
	kEoB2IntroAnimData09,
	kEoB2IntroAnimData10,
	kEoB2IntroAnimData11,
	kEoB2IntroAnimData12,
	kEoB2IntroAnimData13,
	kEoB2IntroAnimData14,
	kEoB2IntroAnimData15,
	kEoB2IntroAnimData16,
	kEoB2IntroAnimData17,
	kEoB2IntroAnimData18,
	kEoB2IntroAnimData19,
	kEoB2IntroAnimData20,
	kEoB2IntroAnimData21,
	kEoB2IntroAnimData22,
	kEoB2IntroAnimData23,
	kEoB2IntroAnimData24,
	kEoB2IntroAnimData25,
	kEoB2IntroAnimData26,
	kEoB2IntroAnimData27,
	kEoB2IntroAnimData28,
	kEoB2IntroAnimData29,
	kEoB2IntroAnimData30,
	kEoB2IntroAnimData31,
	kEoB2IntroAnimData32,
	kEoB2IntroAnimData33,
	kEoB2IntroAnimData34,
	kEoB2IntroAnimData35,
	kEoB2IntroAnimData36,
	kEoB2IntroAnimData37,
	kEoB2IntroAnimData38,
	kEoB2IntroAnimData39,
	kEoB2IntroAnimData40,
	kEoB2IntroAnimData41,
	kEoB2IntroAnimData42,
	kEoB2IntroAnimData43,

	kEoB2IntroShapes00,
	kEoB2IntroShapes01,
	kEoB2IntroShapes04,
	kEoB2IntroShapes07,

	kEoB2FinaleStrings,
	kEoB2CreditsData,
	kEoB2FinaleCPSFiles,
	kEoB2FinaleAnimData00,
	kEoB2FinaleAnimData01,
	kEoB2FinaleAnimData02,
	kEoB2FinaleAnimData03,
	kEoB2FinaleAnimData04,
	kEoB2FinaleAnimData05,
	kEoB2FinaleAnimData06,
	kEoB2FinaleAnimData07,
	kEoB2FinaleAnimData08,
	kEoB2FinaleAnimData09,
	kEoB2FinaleAnimData10,
	kEoB2FinaleAnimData11,
	kEoB2FinaleAnimData12,
	kEoB2FinaleAnimData13,
	kEoB2FinaleAnimData14,
	kEoB2FinaleAnimData15,
	kEoB2FinaleAnimData16,
	kEoB2FinaleAnimData17,
	kEoB2FinaleAnimData18,
	kEoB2FinaleAnimData19,
	kEoB2FinaleAnimData20,
	kEoB2FinaleShapes00,
	kEoB2FinaleShapes03,
	kEoB2FinaleShapes07,
	kEoB2FinaleShapes09,
	kEoB2FinaleShapes10,

	kEoB2NpcShapeData,
	kEoBBaseClassModifierFlags,

	kEoBBaseMonsterStepTable02,
	kEoBBaseMonsterStepTable1,
	kEoBBaseMonsterStepTable2,
	kEoBBaseMonsterStepTable3,
	kEoBBaseMonsterCloseAttPosTable1,
	kEoBBaseMonsterCloseAttPosTable22,
	kEoBBaseMonsterCloseAttUnkTable,
	kEoBBaseMonsterCloseAttChkTable1,
	kEoBBaseMonsterCloseAttChkTable2,
	kEoBBaseMonsterCloseAttDstTable1,
	kEoBBaseMonsterCloseAttDstTable2,

	kEoBBaseMonsterProximityTable,
	kEoBBaseFindBlockMonstersTable,
	kEoBBaseMonsterDirChangeTable,
	kEoBBaseMonsterDistAttStrings,
	kEoBBaseEncodeMonsterDefs,
	kEoBBaseNpcPresets,
	kEoB2Npc1Strings,
	kEoB2Npc2Strings,
	kEoB2MonsterDustStrings,
	kEoB2DreamSteps,
	kEoB2KheldranStrings,
	kEoB2HornStrings,
	kEoB2HornSounds,
	kEoB2WallOfForceDsX,
	kEoB2WallOfForceDsY,
	kEoB2WallOfForceNumW,
	kEoB2WallOfForceNumH,
	kEoB2WallOfForceShpId,

	kRpgCommonDscShapeIndex,
	kRpgCommonDscX,
	kRpgCommonDscTileIndex,
	kRpgCommonDscUnk2,
	kRpgCommonDscDimData1,
	kRpgCommonDscDimData2,
	kRpgCommonDscBlockMap,
	kRpgCommonDscDimMap,
	kRpgCommonDscBlockIndex,

	-1
};

struct GameNeed {
	int game;
	int platform;
	int special;

	const int *entries;
};

const GameNeed gameNeedTable[] = {
	{ kKyra1, kPlatformDOS, kNoSpecial, kyra1FloppyNeed },
	{ kKyra1, kPlatformDOS, kOldFloppy, kyra1FloppyOldNeed },
	{ kKyra1, kPlatformAmiga, kNoSpecial, kyra1AmigaNeed },

	{ kKyra1, kPlatformDOS, kTalkieVersion, kyra1CDNeed },

	{ kKyra1, kPlatformFMTowns, kNoSpecial, kyra1TownsNeed },

	{ kKyra1, kPlatformPC98, kNoSpecial, kyra1PC98Need },

	{ kKyra1, kPlatformDOS, kDemoVersion, kyra1DemoNeed },

	{ kKyra1, kPlatformDOS, kTalkieDemoVersion, kyra1DemoCDNeed },

	{ kKyra2, kPlatformDOS, kNoSpecial, kyra2FloppyNeed },

	{ kKyra2, kPlatformDOS, kTalkieVersion, kyra2CDNeed },

	{ kKyra2, kPlatformDOS, kTalkieDemoVersion, kyra2CDDemoNeed },

	{ kKyra2, kPlatformFMTowns, kNoSpecial, kyra2TownsNeed },

	{ kKyra2, kPlatformPC98, kNoSpecial, kyra2PC98Need },

	{ kKyra2, kPlatformDOS, kDemoVersion, kyra2DemoNeed },

	{ kLoL, kPlatformDOS, kDemoVersion, lolDemoNeed },

	{ kKyra3, kPlatformDOS, kTalkieVersion, kyra3Need },

	{ kLoL, kPlatformDOS, kNoSpecial, lolFloppyNeed },
	{ kLoL, kPlatformPC98, kNoSpecial, lolPC98Need },
	{ kLoL, kPlatformFMTowns, kNoSpecial, lolFMTownsNeed },

	{ kLoL, kPlatformDOS, kTalkieVersion, lolCDNeed },

	{ kEoB1, kPlatformDOS, kNoSpecial, eob1FloppyNeed },

	{ kEoB2, kPlatformDOS, kNoSpecial, eob2FloppyNeed },

	{ -1, -1, -1, 0 }
};

} // end of anonymous namespace

const int *getNeedList(const Game *g) {
	for (const GameNeed *need = gameNeedTable; need->game != -1; ++need) {
		if (need->game == g->game && g->platform == need->platform && need->special == g->special)
			return need->entries;
	}

	return 0;
}
