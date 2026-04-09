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
#include <memory>
#include <vector>

#include "GarrysMod/Lua/Interface.h"
#include "RtMidi.h"

#include "gmcl_rtmidi/classes/RtMidiIn.hpp"
#include "gmcl_rtmidi/classes/RtMidiMessage.hpp"

namespace gmcl_rtmidi {

int RtMidiIn::type = GarrysMod::Lua::Type::None;

RtMidiIn::RtMidiIn(const ::RtMidi::Api &api, const char *client_name, const unsigned int &queue_size) {
	rtmidi = std::make_unique<::RtMidiIn>(api, client_name, queue_size);
}

int RtMidiIn::GetMessage(lua_State *state) {
	const auto self = LUA->GetUserType<RtMidiIn>(1, type);
	double timestamp; std::vector<unsigned char> message;
	try {
		timestamp = self->rtmidi->getMessage(&message);
	}
	catch (const std::exception &error) {
		LUA->ThrowError(error.what());
	}

	LUA->PushUserType(new RtMidiMessage(timestamp, message), RtMidiMessage::type);
	return 1;
}

} // namespace gmcl_rtmidi
