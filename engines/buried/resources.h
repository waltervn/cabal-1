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

// Additional copyright for this file:
// Copyright (C) 1995 Presto Studios, Inc.

#ifndef BURIED_RESOURCES_H
#define BURIED_RESOURCES_H

namespace Buried {

#define IDS_INI_KEY_TRANS_SPEED         868
#define IDS_INI_KEY_CYCLE_CACHING		870

#define IDS_MOVEMENT_DATA_BASE_ID		800

#define IDBD_DIARY1						900
#define IDBD_DIARY2						901

#define IDBD_BC_VIEW_DATA				902

#define IDBD_LETTERS_BOOK_DATA			903

#define IDBD_DIARY1_TRANS_TEXT_BASE		1000
#define IDBD_DIARY2_TRANS_TEXT_BASE		1100
#define IDBD_DIARY3_TRANS_TEXT_BASE		1250

#define IDBD_BLETTER_NUM_LINES_TEXT		1300
#define IDBD_BLETTER_TRANS_TEXT_BASE	1301

#define IDMYTP_WHEELS_LEFT_TRANS_TEXT_BASE		1400
#define IDMYTP_WHEELS_RIGHT_TRANS_TEXT_BASE		1450
#define IDMYTP_WALLS_COMBO_TRANS_TEXT_BASE		1500

#define IDMYTP_INNER_DOOR_TRANS_TEXT			1550
#define IDMYTP_INNER_LEFT_TRANS_TEXT			1551
#define IDMYTP_INNER_MIDDLE_TRANS_TEXT			1552

#define IDMYTP_OUTER_SOUTHLEFT_TRANS_TEXT		1553
#define IDMYTP_OUTER_WEST_TRANS_TEXT			1554
#define IDMYTP_OUTER_NORTH_TRANS_TEXT			1555

#define IDMYMC_WG_DOOR_TOP_TRANS_TEXT			1556
#define IDMYMC_WG_DOOR_RIGHT_TRANS_TEXT			1557

#define IDMYMC_WATERGOD_DOOR_TOP_TRANS_TEXT		1558
#define IDMYMC_WATERGOD_DOOR_RIGHT_TRANS_TEXT	1559

#define IDMYMC_AG_DOOR_TOP_TRANS_TEXT			1560
#define IDMYMC_AG_DOOR_RIGHT_TRANS_TEXT			1561

#define IDMYMC_DEATHGOD_DOOR_TOP_TRANS_TEXT		1562
#define IDMYMC_DEATHGOD_DOOR_RIGHT_TRANS_TEXT	1563

#define IDDS_ELEVATOR_CONTROLS_TEXT_A			1570
#define IDDS_ELEVATOR_CONTROLS_TEXT_B			1571
#define IDDS_ELEVATOR_CONTROLS_TEXT_C			1572
#define IDDS_ELEVATOR_CONTROLS_TEXT_D			1573
#define IDDS_WORKSHOP_TOOLS_TEXT				1574

#define IDMYDG_PUZZLE_BOX_TRANS_TEXT_BASE		1600


#define IDFAKI_SN_CHEESE_GIRL_CODE_TEXT			1650
#define IDFAKI_SN_CHEESE_GIRL_CODE_TITLE		1651
#define IDFAKI_SN_CHEESE_GIRL_ORDER_TEXT		1652

#define IDFAKI_SN_TRANSLATE_CHIP_CODE_TEXT		1653
#define IDFAKI_SN_TRANSLATE_CHIP_CODE_TITLE		1654
#define IDFAKI_SN_TRANSLATE_CHIP_ORDER_TEXT		1655

#define IDFAKI_SN_GENO_SINGLE_CODE_TEXT			1656
#define IDFAKI_SN_GENO_SINGLE_CODE_TITLE		1657
#define IDFAKI_SN_GENO_SINGLE_ORDER_TEXT		1658

#define IDFAKI_SN_SUCCESSFUL_ORDER_TEXT			1659
#define IDFAKI_SN_UNSUCCESSFUL_ORDER_TEXT		1660

#define IDFAKI_AC_ORDER_FOOD_TEXT				1670

#define IDS_MBT_EVIDENCE_PRESENT				1700
#define IDS_MBT_EVIDENCE_ACQUIRED				1701
#define IDS_MBT_EVIDENCE_ALREADY_ACQUIRED		1702
#define IDS_MBT_EVIDENCE_MUST_BE_REVEALED		1703
#define IDS_MBT_EVIDENCE_RIPPLE_DOCUMENTED		1704
#define IDS_MBT_EVIDENCE_NONE_ACQUIRED			1705

#define IDS_MBT_JUMP_LOCKOUT_TEXT               1706

#define IDS_SAVE_GAME_MESSAGE					1710
#define IDS_SEE_DOLL_MESSAGE_A					1711
#define IDS_SEE_DOLL_MESSAGE_B					1712
#define IDS_SEE_DOLL_MESSAGE_C					1713
#define IDS_WM_AI_LAB_TEXT						1714

#define IDS_LENS_FILTER_ACTIVATED				1720
#define IDS_LENS_FILTER_DEACTIVATED				1721

#define IDS_JUMP_BC_REVIEW_MISSION_TEXT_A		1722
#define IDS_JUMP_BC_REVIEW_MISSION_TEXT_B		1723
#define IDS_JUMP_BC_REVIEW_MISSION_TEXT_C		1724
#define IDS_JUMP_BC_REVIEW_MISSION_TEXT_D		1725

#define IDS_LENS_FILTER_ATTACHED				1730
#define IDS_LENS_FILTER_REMOVED                 1731
#define IDS_LENS_FILTER_DENY_REMOVAL            1732

#define IDS_CLOAK_BIOCHIP_ACTIVATE              1733
#define IDS_CLOAK_BIOCHIP_AUTO_ACTIVATE         1734
#define IDS_CLOAK_BIOCHIP_DEACTIVATE            1735

#define IDS_JUMPSUIT_LIGHT_TURN_ON_MESSAGE      1736

#define IDS_HUMAN_PRESENCE_3METERS				1737

#define IDS_DS_WS_UNSTABLE_CYCLE_MESSAGE        1738

#define IDS_DS_WS_CYCLE_PLANS_TEXT_A            1739
#define IDS_DS_WS_CYCLE_PLANS_TEXT_B            1740
#define IDS_DS_WS_CYCLE_PLANS_TEXT_C            1741

#define IDS_AI_ENTERING_PRES_ENV_TEXT           1742

#define IDS_HUMAN_PRESENCE_10METERS             1743
#define IDS_HUMAN_PRESENCE_500METERS            1744

#define IDS_AI_IC_REFILL_OXYGEN_RESERVE         1745

#define IDS_MY_AG_ALTAR_TEXT                    1746
#define IDS_MY_WT_ALTAR_TEXT                    1747
#define IDS_MY_WG_ALTAR_TEXT                    1748

#define IDS_AI_ENTERING_NON_PRES_ENV_TEXT       1749

#define IDS_AS_RA_BEINGS_DETECTED_20_METERS     1750
#define IDS_AS_RA_BEINGS_DETECTED_5_METERS      1751

#define IDS_AS_RA_POD_A_STATUS_TEXT             1752
#define IDS_AS_RA_POD_B_STATUS_TEXT             1753
#define IDS_AS_RA_POD_C_STATUS_TEXT             1754

#define IDS_AI_IS_JUMP_IN_TEXT                  1755

// 1.04+:
#define IDS_AI_IC_OXYGEN_REFILLED       1767
#define IDS_AI_NX_CODE_RESET_MESSAGE    1768


#define IDS_DEATH_SCENE_MESSAGE_TEXT_BASE		1800
#define IDS_DEATH_SCENE_CAUSE_TEXT_BASE			1801


#define IDS_AI_PRES_PANEL_DESC_BASE				5000

#define IDS_AI_PRES_PANEL_ENV_PRES_TEXT			5020
#define IDS_AI_PRES_PANEL_PRES_ENV_TEXT			5021
#define IDS_AI_PRES_PANEL_ZERO_PRES_ENV			5022
#define IDS_AI_PRES_PANEL_ENV_DEPRES			5023
#define IDS_AI_PRES_PANEL_INSUF_OXYGEN			5024
#define IDS_AI_PRES_PANEL_ENV_DEPRES_BREACH		5025
#define IDS_AI_PRES_PANEL_ENV_DEPRES_OBST		5026

#define IDS_AI_OXY_LEVEL_TEXT_TEMPLATE_NORM		5027
#define IDS_AI_OXY_LEVEL_TEXT_TEMPLATE_LOW		5028

#define IDS_UNABLE_TO_TRANSLATE_TEXT            5029

#define IDS_EC_DESC_TEXT_A                      5050
#define IDS_EC_DESC_TEXT_B                      5051
#define IDS_EC_DESC_TEXT_C                      5052
#define IDS_EC_DESC_TEXT_D                      5053
#define IDS_EC_DESC_TEXT_E                      5054
#define IDS_EC_DESC_TEXT_F                      5055
#define IDS_EC_DESC_TEXT_G                      5056
#define IDS_EC_DESC_TEXT_H                      5057
#define IDS_EC_DESC_TEXT_I                      5058
#define IDS_EC_DESC_TEXT_J                      5059
#define IDS_EC_DESC_TEXT_K                      5060



#define IDB_UI_TOP                      12288
#define IDB_UI_LEFT                     12289
#define IDB_UI_RIGHT                    12290
#define IDB_UI_BOTTOM                   12291
#define IDB_INVENTORY_BACKGROUND        12292
#define IDB_INVENTORY_ARROWS            12293
#define IDB_INVENTORY_INFO_BACKGROUND   12294
#define IDB_LIVE_TEXT_BACKGROUND        12295
#define IDB_ARROW_BACKGROUND            12296
#define IDB_ARROW_UP_CLEAR              12297
#define IDB_ARROW_UP_LIT                12298
#define IDB_ARROW_UP_HIGHLIGHTED        12299
#define IDB_ARROW_LEFT_CLEAR            12300
#define IDB_ARROW_LEFT_LIT              12301
#define IDB_ARROW_LEFT_HIGHLIGHTED      12302
#define IDB_ARROW_DOWN_CLEAR            12303
#define IDB_ARROW_DOWN_LIT              12304
#define IDB_ARROW_DOWN_HIGHLIGHTED      12305
#define IDB_ARROW_RIGHT_CLEAR           12306
#define IDB_ARROW_RIGHT_LIT             12307
#define IDB_ARROW_RIGHT_HIGHLIGHTED     12308
#define IDB_ARROW_FORWARD_CLEAR         12309
#define IDB_ARROW_FORWARD_LIT           12310
#define IDB_ARROW_FORWARD_HIGHLIGHTED   12311

#define IDB_UI_WARNING_LIGHT			12315

#define IDB_UI_DATE_BASE				12320

#define IDB_MAINMENU_NORMAL				12348
#define IDB_MAINMENU_DEPRESSED_OVERVIEW			12349
#define IDB_MAINMENU_DEPRESSED_NEW_GAME			12350
#define IDB_MAINMENU_DEPRESSED_PLAY_MODE		12351
#define IDB_MAINMENU_DEPRESSED_PLAY_INRO		12352
#define IDB_MAINMENU_DEPRESSED_RESTORE_GAME		12353
#define IDB_MAINMENU_DEPRESSED_CREDITS			12354
#define IDB_MAINMENU_DEPRESSED_QUIT			12355

#define IDB_DISK_SWAP_DIB_BASE			12360

#define IDB_DEATH_UI_TOP				12400
#define IDB_DEATH_UI_LEFT				12401
#define IDB_DEATH_UI_RIGHT				12402
#define IDB_DEATH_UI_BOTTOM				12403

#define IDB_DEATH_ELIGHT_ON				12404
#define IDB_DEATH_BUTTONS_NORMAL		12405
#define IDB_DEATH_BUTTONS_DEPRESSED		12406

// Full Game:
#define IDB_BCV_INTERFACE_MAIN			12410
#define IDB_BCV_INTERFACE_HANDLE		12411
#define IDB_BCV_INTERFACE_CHECK         12412

#define IDB_DEATH_WT_LOWER_LEFT         12413
#define IDB_DEATH_WT_BUTTONS_NORMAL     12414
#define IDB_DEATH_WT_BUTTONS_DEPRESSED  12415

// Full Game:
#define IDB_BCR_BITMAP_BASE				12450

// Demo:
#define IDB_BCR_BLANK_BACKGROUND		12400
#define IDB_BCR_INTERFACE_MENU			12401
#define IDB_BCR_INTERFACE_EXIT			12402

// Demo:
#define IDB_BCM_INTERFACE_NORMAL		12500
#define IDB_BCM_INTERFACE_SELECTED		12501
#define IDB_BCM_INTERFACE_SLIDER		12502

#define IDB_PICON_BITMAP_BASE			12800
#define IDB_DRAG_BITMAP_BASE			12900
#define IDER_NAV_DB_BASE                16384
#define IDER_SOUND_DB_BASE              16640
#define IDER_ANIM_DB_BASE               16896
#define IDER_AI_DB_BASE					17152

#define IDER_ITEM_DB					4096

#define IDS_BC_RIGHT_FILENAME			6144
#define IDS_BC_MISC_VIEW_FILENAME		6145
#define IDS_BC_JUMP_VIEW_FILENAME		6146
#define IDS_BC_FILES_VIEW_FILENAME		6147
#define IDS_BC_EVIDENCE_VIEW_FILENAME	6148
#define IDS_BC_EVIDENCE_ITEMS_FILENAME	6149
#define IDS_BC_CLOAKING_MOVIE_FILENAME	6150
#define IDS_BC_CLOAKING_SOUND_FILENAME  6151
#define IDS_BC_JUMP_MOVIE_FILENAME		6152
#define IDS_INVENTORY_SPIN_FILENAME		6153
#define IDS_INVENTORY_DRAG_FILENAME		6154
#define IDS_DEATH_CASTLE_FILENAME		6155
#define IDS_DEATH_MAYAN_FILENAME		6156
#define IDS_DEATH_AGENTLAIR_FILENAME	6157
#define IDS_DEATH_DAVINCI_FILENAME		6158
#define IDS_DEATH_AILAB_FILENAME		6159
#define IDS_DEATH_ALIEN_FILENAME		6160
#define IDS_DEATH_FINALE_FILENAME		6161

// Demo-only:
#define IDS_INVENTORY_SPIN_FILENAME_DEMO 10240

#define IDS_BC_JUMP_VIEW_NAV_DATA		6162
#define IDS_INVITEM_LETTER_FILENAME		6163

#define IDS_TITLE_STARFIELD_FILENAME	6164
#define IDS_TITLE_MOVIE_FILENAME		6165

#define IDS_TITLE_PRESTO_LOGO_FILENAME	6166
#define IDS_TITLE_SW_LOGO_FILENAME	    6167

#define IDS_FUTAPT_BOOK_AUDIO_FILENAME	6170

#define IDS_MAYAN_JUMP_MOVIE_FILENAME	6171
#define IDS_CASTLE_JUMP_MOVIE_FILENAME	6172
#define IDS_DAVINCI_JUMP_MOVIE_FILENAME 6173
#define IDS_AILAB_JUMP_MOVIE_FILENAME	6174
#define IDS_FUTAPT_JUMP_MOVIE_FILENAME	6175
#define IDS_BC_JUMP_AUDIO_FILENAME		6176
#define IDS_AGENT3_VIRUS_SOUND_BASE		6180

#define IDS_AGENT3_VIRUS_TEXT_A			6190
#define IDS_AGENT3_VIRUS_TEXT_B			6191
#define IDS_AGENT3_VIRUS_TEXT_C			6192
#define IDS_AGENT3_VIRUS_TEXT_D			6193
#define IDS_AGENT3_VIRUS_PASSWORD		6194
#define IDS_AGENT3_VIRUS_CURSOR			6195
#define IDS_FUTAPT_ENVIRON_DOOR_CLOSE	6196
#define IDS_AGENT3_VIRUS_PW_ACCEPTED    6197

// 1.04+:
#define IDS_AGENT3_VIRUS_NETWORK_TEXT   6198

#define IDS_FOOTSTEPS_FILENAME_BASE		6200

#define IDS_INN_STILL_FRAME_FILENAME	6300
#define IDBD_INN_BINARY_DATA			6301
#define IDBD_INN_MEDIA_BINARY_DATA		6302
#define IDS_INN_AMBIENT_FILENAME		6309
#define IDS_INN_MEDIA_FILENAME_BASE		6310

#define IDS_IF_OV_FULL_SCREEN_DIB		6400
#define IDS_IF_OV_BIOCHIPS_DIB			6401
#define IDS_IF_OV_INVENTORY_DIB			6402
#define IDS_IF_OV_MESSAGE_BOX_DIB		6403
#define IDS_IF_OV_NAV_ARROWS_DIB		6404
#define IDS_IF_OV_NAV_ARROWS_AUDIO		6410
#define IDS_IF_OV_INVENTORY_AUDIO		6411
#define IDS_IF_OV_BIOCHIPS_AUDIO		6412
#define IDS_IF_OV_MESSAGE_BOX_AUDIO		6413
#define IDS_IF_OV_FURTHER_INFO_AUDIO	6414

#define IDS_CREDITS_MAIN_FILENAME		6420
#define IDS_CREDITS_HIGHLIGHT_FILENAME	6421
#define IDS_CREDITS_MOVIE_FILENAME		6422

#define IDES_ITEM_TITLE_BASE			8192
#define IDES_ITEM_DESC_BASE				8256

// 1.04+:
#define IDS_AL_VULGAR_LANG_A            9000
#define IDS_AL_VULGAR_LANG_B            9001
#define IDS_AL_VULGAR_LANG_C            9002
#define IDS_AL_VULGAR_LANG_D            9003
#define IDS_AL_VULGAR_LANG_E            9004
#define IDS_AL_VULGAR_LANG_F            9005
#define IDS_AL_VULGAR_LANG_G            9006
#define IDS_AL_VULGAR_LANG_H            9007
#define IDS_AL_VULGAR_LANG_I            9009
#define IDS_AL_CASTRATION_TEXT          9016
#define IDS_AS_VISIBILITY_MESSAGE       9022
#define IDS_COMPL_WALK_SCORE_DESC_TEMPL 9031
#define IDS_DEATH_WALK_SCORE_DESC_TEMPL 9031
#define IDS_COMPL_WALK_SCORE_AMT_TEMPL  9032
#define IDS_DEATH_WALK_SCORE_AMT_TEMPL  9032
#define IDS_COMPL_SCORE_DESC_TEMPL      9033
#define IDS_DEATH_SCORE_DESC_TEMPL      9033
#define IDS_COMPL_SCORE_AMT_TEMPL       9034
#define IDS_DEATH_SCORE_AMT_TEMPL       9034
#define IDS_COMPL_FINAL_SCORE_TEMPL     9035
#define IDS_DEATH_FINAL_SCORE_TEMPL     9035

// 1.04+:
#define IDS_MYTP_WALKTHROUGH_HINT_TEXT  9080
#define IDS_PLAY_MODE_WALKTHROUGH_TEXT  9085
#define IDS_PLAY_MODE_NORMAL_TEXT       9086
#define IDS_OLD_APT_RECALL_MESSAGE      9088


#define IDES_FILENAME_BASE              17408
#define IDES_STRING_BASE                21504

#define RESID_NAVDB_BASE				16384
#define RESID_SOUNDDB_BASE				16640
#define RESID_ANIMDB_BASE				16896
#define RESID_AI_DB_BASE				17152
	
#define RESID_FILENAMES_BASE			17408
#define RESID_STRINGS_BASE				21504
#define RESID_TRANSLATOR_TEXT_BASE		8192

#define RESOFFSET_NAVDB_TIMEZONE		16
#define RESOFFSET_SOUNDDB_TIMEZONE		16
#define RESOFFSET_ANIMDB_TIMEZONE		16
#define RESOFFSET_AI_DB_TIMEZONE		16

#define RESOFFSET_FILENAME_TIMEZONE		256
#define RESOFFSET_FILENAME_ENVIRON		16

#define LOADSTRING_BUFFER_SIZE			512
#define LOADSTRING_NUM_BUFFERS			6

#define SF_STILLS		0
#define SF_CYCLES		1
#define SF_NAVIGATION	2
#define SF_AMBIENT		15

#define DIB_FRAME_WIDTH		432
#define DIB_FRAME_HEIGHT	189

} // End of namespace Buried

#endif
