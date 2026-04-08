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

#include "gmcl_rtmidi/common.hpp"
#include "gmcl_rtmidi/classes/RtMidiMessage.hpp"
#include "gmcl_rtmidi/classes/RtMidiIn.hpp"
#include "gmcl_rtmidi/classes/RtMidiOut.hpp"
#include "gmcl_rtmidi/libraries/rtmidi.hpp"

GMOD_MODULE_OPEN() {
	gmcl_rtmidi::RtMidiMessage::type = LUA->CreateMetaTable("RtMidiMessage");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiMessage::__index);
	LUA->SetField(-2, "__index");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiMessage::__gc);
	LUA->SetField(-2, "__gc");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiMessage::__tostring);
	LUA->SetField(-2, "__tostring");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiMessage::GetTimestamp);
	LUA->SetField(-2, "GetTimestamp");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiMessage::GetStatusByte);
	LUA->SetField(-2, "GetStatusByte");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiMessage::GetDataBytes);
	LUA->SetField(-2, "GetDataBytes");

	gmcl_rtmidi::RtMidiIn::type = LUA->CreateMetaTable("RtMidiIn");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiIn::__index);
	LUA->SetField(-2, "__index");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiIn::__gc);
	LUA->SetField(-2, "__gc");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiIn::__tostring);
	LUA->SetField(-2, "__tostring");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiIn::GetCurrentAPI);
	LUA->SetField(-2, "GetCurrentAPI");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiIn::GetCompiledAPI);
	LUA->SetField(-2, "GetCompiledAPI");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiIn::GetAPIName);
	LUA->SetField(-2, "GetAPIName");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiIn::GetAPIDisplayName);
	LUA->SetField(-2, "GetAPIDisplayName");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiIn::IsPortOpen);
	LUA->SetField(-2, "IsPortOpen");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiIn::GetPortCount);
	LUA->SetField(-2, "GetPortCount");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiIn::GetPortName);
	LUA->SetField(-2, "GetPortName");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiIn::ClosePort);
	LUA->SetField(-2, "ClosePort");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiIn::OpenPort);
	LUA->SetField(-2, "OpenPort");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiIn::GetMessage);
	LUA->SetField(-2, "GetMessage");

	gmcl_rtmidi::RtMidiOut::type = LUA->CreateMetaTable("RtMidiOut");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiOut::__index);
	LUA->SetField(-2, "__index");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiOut::__gc);
	LUA->SetField(-2, "__gc");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiOut::__tostring);
	LUA->SetField(-2, "__tostring");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiOut::GetCurrentAPI);
	LUA->SetField(-2, "GetCurrentAPI");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiOut::GetCompiledAPI);
	LUA->SetField(-2, "GetCompiledAPI");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiOut::GetAPIName);
	LUA->SetField(-2, "GetAPIName");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiOut::GetAPIDisplayName);
	LUA->SetField(-2, "GetAPIDisplayName");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiOut::IsPortOpen);
	LUA->SetField(-2, "IsPortOpen");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiOut::GetPortCount);
	LUA->SetField(-2, "GetPortCount");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiOut::GetPortName);
	LUA->SetField(-2, "GetPortName");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiOut::ClosePort);
	LUA->SetField(-2, "ClosePort");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiOut::OpenPort);
	LUA->SetField(-2, "OpenPort");
	LUA->PushCFunction(gmcl_rtmidi::RtMidiOut::SendMessage);
	LUA->SetField(-2, "SendMessage");

	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	LUA->CreateTable();
	LUA->PushString(GMCL_RTMIDI_VERSION);
	LUA->SetField(-2, "version");
	LUA->PushString(RTMIDI_VERSION);
	LUA->SetField(-2, "version_internal");
	LUA->PushCFunction(gmcl_rtmidi::rtmidi::CreateInput);
	LUA->SetField(-2, "CreateInput");
	LUA->PushCFunction(gmcl_rtmidi::rtmidi::CreateOutput);
	LUA->SetField(-2, "CreateOutput");
	LUA->SetField(-2, "rtmidi");

	return 0;
}

GMOD_MODULE_CLOSE() {
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_REG);
	LUA->PushNil();
	LUA->SetField(-2, "RtMidiMessage");
	LUA->PushNil();
	LUA->SetField(-2, "RtMidiIn");
	LUA->PushNil();
	LUA->SetField(-2, "RtMidiOut");

	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	LUA->PushNil();
	LUA->SetField(-2, "rtmidi");

	return 0;
}
