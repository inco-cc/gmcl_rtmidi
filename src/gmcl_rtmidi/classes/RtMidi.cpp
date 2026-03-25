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

#include <format>
#include "gmcl_rtmidi/classes/RtMidi.hpp"

namespace gmcl_rtmidi {

int RtMidi::__index(lua_State *state, const int &type) {
	LUA->PushMetaTable(type);
	LUA->GetField(-1, LUA->GetString(2));
	return 1;
}

int RtMidi::__gc(lua_State *state, const int &type) {
	delete get_self<RtMidi>(state, type);
	return 0;
}

int RtMidi::__tostring(lua_State *state, const int &type) {
	LUA->CheckType(1, type);
	LUA->GetField(1, "MetaName");
	auto type_name = LUA->GetString();

	LUA->GetField(1, "GetCurrentAPI");
	LUA->Push(1);
	LUA->Call(1, 1);
	auto api = LUA->GetNumber();

	LUA->GetField(1, "GetAPIName");
	LUA->Push(1);
	LUA->PushNumber(api);
	LUA->Call(2, 1);
	auto api_name = LUA->GetString();

	LUA->PushString(std::format("{} [{}]", type_name, api_name).c_str());
	return 1;
}

int RtMidi::GetCurrentAPI(lua_State *state, const int &type) {
	LUA->PushNumber(get_self<RtMidi>(state, type)->rtmidi->getCurrentApi());
	return 1;
}

int RtMidi::GetAPIName(lua_State *state, const int &type) {
	LUA->PushString(get_self<RtMidi>(state, type)->rtmidi->getApiName(
		(::RtMidi::Api)LUA->GetNumber(2)).c_str());
	return 1;
}

int RtMidi::IsPortOpen(lua_State *state, const int &type) {
	LUA->PushBool(get_self<RtMidi>(state, type)->rtmidi->isPortOpen());
	return 1;
}

int RtMidi::GetPortCount(lua_State *state, const int &type) {
	LUA->PushNumber(get_self<RtMidi>(state, type)->rtmidi->getPortCount());
	return 1;
}

int RtMidi::GetPortName(lua_State *state, const int &type) {
	LUA->PushString(get_self<RtMidi>(state, type)->rtmidi->getPortName(
		(unsigned int)LUA->CheckNumber(2)).c_str());
	return 1;
}

} // namespace gmcl_rtmidi
