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

#ifndef BACKENDS_PLATFORM_MACOSX_COMPAT_H
#define BACKENDS_PLATFORM_MACOSX_COMPAT_H

#include <AvailabilityMacros.h>

// Redefine the DEPRECATED_ATTRIBUTE macro to prevent the compiler from warning.
// For compatibility, we'll build in some bits that may not be used in later
// revisions of the operating system. The deprecation warnings just annoy the
// developer coding.
#undef DEPRECATED_ATTRIBUTE
#define DEPRECATED_ATTRIBUTE

#endif
