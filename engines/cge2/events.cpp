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

/*
 * This code is based on original Sfinx source code
 * Copyright (c) 1994-1997 Janus B. Wisniewski and L.K. Avalon
 */

#include "gui/saveload.h"
#include "gui/about.h"
#include "gui/message.h"
#include "common/config-manager.h"
#include "common/events.h"
#include "engines/advancedDetector.h"
#include "cge2/events.h"
#include "cge2/text.h"
#include "cge2/cge2_main.h"

namespace CGE2 {

/*----------------- KEYBOARD interface -----------------*/

Keyboard::Keyboard(CGE2Engine *vm) : _client(NULL), _vm(vm) {
	warning("STUB: Keyboard::Keyboard() - Recheck the whole implementation!!!");
}

Keyboard::~Keyboard() {
}

Sprite *Keyboard::setClient(Sprite *spr) {
	warning("STUB: Keyboard::setClient()");
	return spr;
}

bool Keyboard::getKey(Common::Event &event) {
	warning("STUB: Keyboard::getKey()");
	return false;
}

void Keyboard::newKeyboard(Common::Event &event) {
	warning("STUB: Keyboard::newKeyboard()");
}

/*----------------- MOUSE interface -----------------*/

Mouse::Mouse(CGE2Engine *vm) : Sprite(vm), _busy(NULL), _hold(NULL), _hx(0), _vm(vm) {
	warning("STUB: Mouse::Mouse() - Recheck the whole implementation!!!");
}

Mouse::~Mouse() {
	warning("STUB: Mouse::~Mouse()");
}

void Mouse::on() {
	warning("STUB: Mouse::on()");
}

void Mouse::off() {
	warning("STUB: Mouse::off()");
}

void Mouse::newMouse(Common::Event &event) {
	warning("STUB: Mouse::newMouse()");
}

} // End of namespace CGE2
