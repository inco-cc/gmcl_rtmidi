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

int rtmidi::CreateInput(lua_State *state) {
	try {
		auto api = ::RtMidi::Api::UNSPECIFIED;
		auto client_name = "Garry's Mod Input Client";
		auto queue_size = 100U;

		if (LUA->GetType(1) > GarrysMod::Lua::Type::Nil)
			api = (::RtMidi::Api)LUA->CheckNumber(1);
		if (LUA->GetType(2) > GarrysMod::Lua::Type::Nil)
			client_name = LUA->CheckString(2);
		if (LUA->GetType(3) > GarrysMod::Lua::Type::Nil)
			queue_size = (unsigned int)LUA->CheckNumber(3);

		LUA->PushUserType(new RtMidiIn(api, client_name, queue_size), RtMidiIn::type);
	}
	catch (const std::exception &ex) {
		LUA->ThrowError(ex.what());
	}
	return 1;
}

int rtmidi::CreateOutput(lua_State *state) {
	try {
		auto api = ::RtMidi::Api::UNSPECIFIED;
		auto client_name = "Garry's Mod Output Client";

		if (LUA->GetType(1) > GarrysMod::Lua::Type::Nil)
			api = (::RtMidi::Api)LUA->CheckNumber(1);
		if (LUA->GetType(2) > GarrysMod::Lua::Type::Nil)
			client_name = LUA->CheckString(2);

		LUA->PushUserType(new RtMidiOut(api, client_name), RtMidiOut::type);
	}
	catch (const std::exception &ex) {
		LUA->ThrowError(ex.what());
	}
	return 1;
}

} // namespace gmcl_rtmidi
