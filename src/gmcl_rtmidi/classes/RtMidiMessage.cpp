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
#include "gmcl_rtmidi/classes/RtMidiMessage.hpp"

namespace gmcl_rtmidi {

int RtMidiMessage::type = GarrysMod::Lua::Type::None;

RtMidiMessage::RtMidiMessage(const double &timestamp, const std::vector<unsigned char> &message) {
	this->timestamp = timestamp;
	this->message = message;
}

int RtMidiMessage::__index(lua_State *state) {
	LUA->PushMetaTable(type);
	LUA->GetField(-1, LUA->GetString(2));
	return 1;
}

int RtMidiMessage::__gc(lua_State *state) {
	auto self = LUA->GetUserType<RtMidiMessage>(1, type);
	if (self != nullptr) delete self;
	return 0;
}

int RtMidiMessage::__tostring(lua_State *state) {
	LUA->GetField(1, "MetaName");
	auto type_name = LUA->GetString();

	LUA->GetField(1, "GetStatusByte");
	LUA->Push(1);
	LUA->Call(1, 1);
	const auto status_byte = LUA->GetNumber();

	LUA->PushString(std::format("{} [{}]", type_name, status_byte).c_str());
	return 1;
}

int RtMidiMessage::GetTimestamp(lua_State *state) {
	const auto self = LUA->GetUserType<RtMidiMessage>(1, type);
	LUA->PushNumber(self->timestamp);
	return 1;
}

int RtMidiMessage::GetStatusByte(lua_State *state) {
	const auto self = LUA->GetUserType<RtMidiMessage>(1, type);
	LUA->PushNumber(!self->message.empty() ? self->message.at(0) : -1);
	return 1;
}

int RtMidiMessage::GetDataBytes(lua_State *state) {
	const auto self = LUA->GetUserType<RtMidiMessage>(1, type);
	LUA->CreateTable();
	for (int i = 1; i < self->message.size(); i++) {
		LUA->PushNumber(LUA->ObjLen(-1) + 1);
		LUA->PushNumber(self->message.at(i));
		LUA->SetTable(-3);
	}
	return 1;
}

} // namespace gmcl_rtmidi
