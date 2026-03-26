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

#pragma once

#include <memory>
#include "gmcl_rtmidi/classes/RtMidi.hpp"

namespace gmcl_rtmidi {

class RtMidiIn : RtMidi {
private:
	std::unique_ptr<::RtMidiIn> rtmidi_in;

public:
	RtMidiIn(lua_State *state);

	static int type;

	static int __index(lua_State *state) { return RtMidi::__index(state, type); }
	static int __gc(lua_State *state) { return RtMidi::__gc(state, type); }
	static int __tostring(lua_State *state) { return RtMidi::__tostring(state, type); }
	static int GetCurrentAPI(lua_State *state) { return RtMidi::GetCurrentAPI(state, type); }
	static int GetAPIName(lua_State *state) { return RtMidi::GetAPIName(state, type); }
	static int IsPortOpen(lua_State *state) { return RtMidi::IsPortOpen(state, type); }
	static int GetPortCount(lua_State *state) { return RtMidi::GetPortCount(state, type); }
	static int GetPortName(lua_State *state) { return RtMidi::GetPortName(state, type); }
};

} // namespace gmcl_rtmidi
