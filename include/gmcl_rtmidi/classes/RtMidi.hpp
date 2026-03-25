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

#include "RtMidi.h"
#include "GarrysMod/Lua/Interface.h"

namespace gmcl_rtmidi {

class RtMidi {
protected:
	::RtMidi *rtmidi;

	template <class T>
	static T *get_self(lua_State *state, const int &type) {
		LUA->CheckType(1, type);
		return LUA->GetUserType<T>(1, type);
	}

	static int __index(lua_State *state, const int &type);
	static int __gc(lua_State *state, const int &type);
	static int __tostring(lua_State *state, const int &type);
	static int GetCurrentAPI(lua_State *state, const int &type);
	static int GetAPIName(lua_State *state, const int &type);
	static int IsPortOpen(lua_State *state, const int &type);
	static int GetPortCount(lua_State *state, const int &type);
	static int GetPortName(lua_State *state, const int &type);

public:
	virtual ~RtMidi() {}
};

} // namespace gmcl_rtmidi
