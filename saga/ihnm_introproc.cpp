/* ScummVM - Scumm Interpreter
 * Copyright (C) 2004-2005 The ScummVM project
 *
 * The ReInherit Engine is (C)2000-2003 by Daniel Balsom.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header$
 *
 */

// "I Have No Mouth" Intro sequence scene procedures

#include "saga/saga.h"
#include "saga/gfx.h"

#include "saga/animation.h"
#include "saga/events.h"
#include "saga/rscfile_mod.h"
#include "saga/sndres.h"
#include "saga/music.h"

#include "saga/scene.h"

namespace Saga {

SCENE_RESLIST IHNM_IntroMovie1RL[] = {
	{30, SAGA_BG_IMAGE, 0, 0} ,
	{31, SAGA_ANIM_1, 0, 0}
};

SceneDescription IHNM_IntroMovie1Desc = {
	0, 0, 0, 0, 0, 0, 0, 0,
	IHNM_IntroMovie1RL,
	ARRAYSIZE(IHNM_IntroMovie1RL)
};

SCENE_RESLIST IHNM_IntroMovie2RL[] = {
	{32, SAGA_BG_IMAGE, 0, 0} ,
	{33, SAGA_ANIM_1, 0, 0}
};

SceneDescription IHNM_IntroMovie2Desc = {
	0, 0, 0, 0, 0, 0, 0, 0,
	IHNM_IntroMovie2RL,
	ARRAYSIZE(IHNM_IntroMovie2RL)
};

SCENE_RESLIST IHNM_IntroMovie3RL[] = {
	{34, SAGA_BG_IMAGE, 0, 0},
	{35, SAGA_ANIM_1, 0, 0}
};

SceneDescription IHNM_IntroMovie3Desc = {
	0, 0, 0, 0, 0, 0, 0, 0,
	IHNM_IntroMovie3RL,
	ARRAYSIZE(IHNM_IntroMovie3RL)
};

SCENE_RESLIST IHNM_IntroMovie4RL[] = {
	{1227, SAGA_BG_IMAGE, 0, 0},
	{1226, SAGA_ANIM_1, 0, 0}
};

SceneDescription IHNM_IntroMovie4Desc = {
	0, 0, 0, 0, 0, 0, 0, 0,
	IHNM_IntroMovie4RL,
	ARRAYSIZE(IHNM_IntroMovie4RL)
};

SCENE_QUEUE IHNM_IntroList[] = {
	{0, &IHNM_IntroMovie1Desc, BY_DESC, Scene::SC_IHNMIntroMovieProc1, 0, SCENE_NOFADE},
	{0, &IHNM_IntroMovie2Desc, BY_DESC, Scene::SC_IHNMIntroMovieProc2, 0, SCENE_NOFADE},
	{0, &IHNM_IntroMovie3Desc, BY_DESC, Scene::SC_IHNMIntroMovieProc3, 0, SCENE_NOFADE},
	{0, &IHNM_IntroMovie4Desc, BY_DESC, Scene::SC_IHNMHateProc, 0, SCENE_NOFADE}
};

int Scene::IHNMStartProc() {
	size_t n_introscenes;
	size_t i;

	SCENE_QUEUE first_scene;

	n_introscenes = ARRAYSIZE(IHNM_IntroList);

	for (i = 0; i < n_introscenes; i++) {
		_vm->_scene->queueScene(&IHNM_IntroList[i]);
	}

	// FIXME: I believe I've found the correct scene, but since we do not
	// yet support IHNM script loading it won't actually do anything. Also,
	// it will cause the end titles music to play, which is wrong. (But
	// hey, it's a nice piece of music!)

	first_scene.load_flag = BY_SCENE;
	first_scene.scene_n = _vm->getStartSceneNumber();
	first_scene.scene_skiptarget = 1;
	first_scene.scene_proc = NULL;
	first_scene.fadeType = SCENE_FADE;

	_vm->_scene->queueScene(&first_scene);

	return SUCCESS;
}

int Scene::SC_IHNMIntroMovieProc1(int param, SCENE_INFO *scene_info, void *refCon) {
	return ((Scene *)refCon)->IHNMIntroMovieProc1(param, scene_info);
}

int Scene::IHNMIntroMovieProc1(int param, SCENE_INFO *scene_info) {
	EVENT event;
	EVENT *q_event;

	switch (param) {
	case SCENE_BEGIN:
		// Background for intro scene is the first frame of the
		// intro animation; display it and set the palette
		event.type = ONESHOT_EVENT;
		event.code = BG_EVENT;
		event.op = EVENT_DISPLAY;
		event.param = SET_PALETTE;
		event.time = 0;

		q_event = _vm->_events->queue(&event);

		_vm->_anim->setFrameTime(0, IHNM_INTRO_FRAMETIME);
		_vm->_anim->setFlag(0, ANIM_ENDSCENE);

		event.type = ONESHOT_EVENT;
		event.code = ANIM_EVENT;
		event.op = EVENT_PLAY;
		event.param = 0;
		event.time = 0;

		q_event = _vm->_events->chain(q_event, &event);
		break;
	default:
		break;
	}

	return 0;
}

int Scene::SC_IHNMIntroMovieProc2(int param, SCENE_INFO *scene_info, void *refCon) {
	return ((Scene *)refCon)->IHNMIntroMovieProc2(param, scene_info);
}

int Scene::IHNMIntroMovieProc2(int param, SCENE_INFO *scene_info) {
	EVENT event;
	EVENT *q_event;
	PALENTRY *pal;

	static PALENTRY current_pal[PAL_ENTRIES];

	switch (param) {
	case SCENE_BEGIN:
		// Fade to black out of the intro CyberDreams logo anim
		_vm->_gfx->getCurrentPal(current_pal);

		event.type = CONTINUOUS_EVENT;
		event.code = PAL_EVENT;
		event.op = EVENT_PALTOBLACK;
		event.time = 0;
		event.duration = IHNM_PALFADE_TIME;
		event.data = current_pal;

		q_event = _vm->_events->queue(&event);

		// Background for intro scene is the first frame of the
		// intro animation; display it but don't set palette
		event.type = ONESHOT_EVENT;
		event.code = BG_EVENT;
		event.op = EVENT_DISPLAY;
		event.param = NO_SET_PALETTE;
		event.time = 0;

		q_event = _vm->_events->chain(q_event, &event);

		_vm->_anim->setCycles(0, -1);

		// Unlike the original, we keep the logo spinning during the
		// palette fades. We don't have to, but I think it looks better
		// that way.

		event.type = ONESHOT_EVENT;
		event.code = ANIM_EVENT;
		event.op = EVENT_PLAY;
		event.param = 0;
		event.time = 0;

		q_event = _vm->_events->chain(q_event, &event);

		// Fade in from black to the scene background palette
		_vm->_scene->getBGPal(&pal);

		event.type = CONTINUOUS_EVENT;
		event.code = PAL_EVENT;
		event.op = EVENT_BLACKTOPAL;
		event.time = 0;
		event.duration = IHNM_PALFADE_TIME;
		event.data = pal;

		q_event = _vm->_events->chain(q_event, &event);

		// Fade to black after looping animation for a while
		event.type = CONTINUOUS_EVENT;
		event.code = PAL_EVENT;
		event.op = EVENT_PALTOBLACK;
		event.time = IHNM_DGLOGO_TIME;
		event.duration = IHNM_PALFADE_TIME;
		event.data = pal;

		q_event = _vm->_events->chain(q_event, &event);

		// Queue end of scene
		event.type = ONESHOT_EVENT;
		event.code = SCENE_EVENT;
		event.op = EVENT_END;
		event.time = 0;

		q_event = _vm->_events->chain(q_event, &event);
		break;
	default:
		break;
	}

	return 0;
}

int Scene::SC_IHNMIntroMovieProc3(int param, SCENE_INFO *scene_info, void *refCon) {
	return ((Scene *)refCon)->IHNMIntroMovieProc3(param, scene_info);
}

int Scene::IHNMIntroMovieProc3(int param, SCENE_INFO *scene_info) {
	EVENT event;
	EVENT *q_event;
	PALENTRY *pal;
	static PALENTRY current_pal[PAL_ENTRIES];

	switch (param) {
	case SCENE_BEGIN:
		// Fade to black out of the intro DG logo anim
		_vm->_gfx->getCurrentPal(current_pal);

		event.type = CONTINUOUS_EVENT;
		event.code = PAL_EVENT;
		event.op = EVENT_PALTOBLACK;
		event.time = 0;
		event.duration = IHNM_PALFADE_TIME;
		event.data = current_pal;

		q_event = _vm->_events->queue(&event);

		// Music, maestro

		// In the GM file, this music also appears as tracks 7, 13, 19,
		// 25 and 31, but only track 1 sounds right with the FM music.

		event.type = ONESHOT_EVENT;
		event.code = MUSIC_EVENT;
		event.param = 1;
		event.param2 = 0;
		event.op = EVENT_PLAY;
		event.time = 0;

		q_event = _vm->_events->chain(q_event, &event);

		// Background for intro scene is the first frame of the intro
		// animation; display it but don't set palette
		event.type = ONESHOT_EVENT;
		event.code = BG_EVENT;
		event.op = EVENT_DISPLAY;
		event.param = NO_SET_PALETTE;
		event.time = 0;

		q_event = _vm->_events->chain(q_event, &event);

		// Fade in from black to the scene background palette
		_vm->_scene->getBGPal(&pal);

		event.type = CONTINUOUS_EVENT;
		event.code = PAL_EVENT;
		event.op = EVENT_BLACKTOPAL;
		event.time = 0;
		event.duration = IHNM_PALFADE_TIME;
		event.data = pal;

		q_event = _vm->_events->chain(q_event, &event);

		event.type = ONESHOT_EVENT;
		event.code = ANIM_EVENT;
		event.op = EVENT_PLAY;
		event.param = 0;
		event.time = 0;

		q_event = _vm->_events->chain(q_event, &event);

		// Queue end of scene after a while
		// TODO: I've increased the delay so the speech won't start
		// until the music has ended. Could someone verify if that's
		// the correct behaviour?
		event.type = ONESHOT_EVENT;
		event.code = SCENE_EVENT;
		event.op = EVENT_END;
		event.time = _vm->_music->hasAdlib() ? IHNM_TITLE_TIME_FM : IHNM_TITLE_TIME_GM;

		q_event = _vm->_events->chain(q_event, &event);
		break;
	default:
		break;
	}

	return 0;
}

int Scene::SC_IHNMHateProc(int param, SCENE_INFO *scene_info, void *refCon) {
	return ((Scene *)refCon)->IHNMHateProc(param, scene_info);
}

int Scene::IHNMHateProc(int param, SCENE_INFO *scene_info) {
	EVENT event;
	EVENT *q_event;

	switch (param) {
	case SCENE_BEGIN:
		_vm->_anim->setCycles(0, -1);

		// Start "hate" animation
		event.type = ONESHOT_EVENT;
		event.code = ANIM_EVENT;
		event.op = EVENT_PLAY;
		event.param = 0;
		event.time = 0;

		q_event = _vm->_events->queue(&event);

		// More music
		event.type = ONESHOT_EVENT;
		event.code = MUSIC_EVENT;
		event.param = 32;
		event.param2 = MUSIC_LOOP;
		event.op = EVENT_PLAY;
		event.time = 0;

		q_event = _vm->_events->chain(q_event, &event);

		// Background for intro scene is the first frame of the
		// intro animation; display it and set the palette
		event.type = ONESHOT_EVENT;
		event.code = BG_EVENT;
		event.op = EVENT_DISPLAY;
		event.param = SET_PALETTE;
		event.time = 0;

		q_event = _vm->_events->chain(q_event, &event);

		// Play voice
		event.type = ONESHOT_EVENT;
		event.code = VOICE_EVENT;
		event.op = EVENT_PLAY;
		event.param = 0;
		event.time = 0;

		q_event = _vm->_events->chain(q_event, &event);

		// Background sound
		event.type = ONESHOT_EVENT;
		event.code = SOUND_EVENT;
		event.op = EVENT_PLAY;
		event.param = 260;
		event.param2 = 255;	// FIXME: Verify volume
		event.param3 = SOUND_LOOP;
		event.time = 0;

		q_event = _vm->_events->chain(q_event, &event);

		// End background sound after the voice has finished
		event.type = ONESHOT_EVENT;
		event.code = SOUND_EVENT;
		event.op = EVENT_STOP;
		event.time = _vm->_sndRes->getVoiceLength(0);

		q_event = _vm->_events->chain(q_event, &event);

		// End scene after the voice has finished
		event.type = ONESHOT_EVENT;
		event.code = SCENE_EVENT;
		event.op = EVENT_END;
		event.time = 0;

		q_event = _vm->_events->chain(q_event, &event);
		break;
	default:
		break;
	}

	return 0;
}

} // End of namespace Saga
