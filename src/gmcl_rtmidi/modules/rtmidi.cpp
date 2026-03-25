/*
 * Copyright (c) 2026 Brandon Little <blittle@inco.cc>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#define GMOD_ALLOW_DEPRECATED

#include <exception>
#include "gmcl_rtmidi/modules/rtmidi.hpp"
#include "gmcl_rtmidi/classes/RtMidiIn.hpp"
#include "gmcl_rtmidi/classes/RtMidiOut.hpp"

namespace gmcl_rtmidi {

const char *rtmidi::version = "0.1.0";
const char *rtmidi::version_internal = RTMIDI_VERSION;

int rtmidi::CreateInput(lua_State *state) {
	try {
		LUA->PushUserType(new RtMidiIn(state), RtMidiIn::type);
	} catch (const std::exception &ex) {
		LUA->ThrowError(ex.what());
	} return 1;
}

int rtmidi::CreateOutput(lua_State *state) {
	try {
		LUA->PushUserType(new RtMidiOut(state), RtMidiOut::type);
	} catch (const std::exception &ex) {
		LUA->ThrowError(ex.what());
	} return 1;
}

} // namespace gmcl_rtmidi
