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
#include <format>
#include "RtMidi.h"
#include "GarrysMod/Lua/Interface.h"

namespace gmcl_rtmidi {

template <class T, class U> class RtMidi {
protected:
	std::unique_ptr<U> rtmidi;

public:
	static int __index(lua_State *state) {
		LUA->PushMetaTable(T::type);
		LUA->GetField(-1, LUA->GetString(2));
		return 1;
	}

	static int __gc(lua_State *state) {
		auto self = LUA->GetUserType<T>(1, T::type);
		if (self != nullptr) delete self;
		return 0;
	}

	static int __tostring(lua_State *state) {
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

	static int GetCurrentAPI(lua_State *state) {
		const auto self = LUA->GetUserType<T>(1, T::type);
		LUA->PushNumber(self->rtmidi->getCurrentApi());
		return 1;
	}

	static int GetAPIName(lua_State *state) {
		const auto self = LUA->GetUserType<T>(1, T::type);
		const auto api = (::RtMidi::Api)LUA->GetNumber(2);
		LUA->PushString(self->rtmidi->getApiName(api).c_str());
		return 1;
	}

	static int IsPortOpen(lua_State *state) {
		const auto self = LUA->GetUserType<T>(1, T::type);
		LUA->PushBool(self->rtmidi->isPortOpen());
		return 1;
	}

	static int GetPortCount(lua_State *state) {
		const auto self = LUA->GetUserType<T>(1, T::type);
		LUA->PushNumber(self->rtmidi->getPortCount());
		return 1;
	}

	static int GetPortName(lua_State *state) {
		const auto self = LUA->GetUserType<T>(1, T::type);
		const auto port = (unsigned int)LUA->CheckNumber(2);
		LUA->PushString(self->rtmidi->getPortName(port).c_str());
		return 1;
	}
};

} // namespace gmcl_rtmidi
