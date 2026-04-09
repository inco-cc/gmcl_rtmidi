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

#include <vector>

#include "GarrysMod/Lua/Interface.h"

namespace gmcl_rtmidi {

class RtMidiMessage {
private:
	double timestamp;
	std::vector<unsigned char> message;

public:
	static int type;

	RtMidiMessage(const double &timestamp, const std::vector<unsigned char> &message);

	static int __index(lua_State *state);
	static int __gc(lua_State *state);
	static int __tostring(lua_State *state);

	static int GetTimestamp(lua_State *state);
	static int GetStatusByte(lua_State *state);
	static int GetDataBytes(lua_State *state);
};

} // namespace gmcl_rtmidi
