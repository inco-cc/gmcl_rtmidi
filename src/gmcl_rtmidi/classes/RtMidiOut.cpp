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

#include "gmcl_rtmidi/classes/RtMidiOut.hpp"

namespace gmcl_rtmidi {

int RtMidiOut::type = GarrysMod::Lua::Type::None;

RtMidiOut::RtMidiOut(const ::RtMidi::Api &api, const char *client_name) {
	rtmidi = std::make_unique<::RtMidiOut>(api, client_name);
}

int RtMidiOut::SendMessage(lua_State *state) {
	std::vector<unsigned char> message;
	for (int i = 2; i <= LUA->Top(); i++)
		message.push_back((unsigned char)LUA->CheckNumber(i));

	const auto self = LUA->GetUserType<RtMidiOut>(1, type);
	try {
		self->rtmidi->sendMessage(&message);
	}
	catch (const std::exception &error) {
		LUA->ThrowError(error.what());
	}

	return 0;
}

} // namespace gmcl_rtmidi
