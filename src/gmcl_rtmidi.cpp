/*
 * Copyright (c) 2021 Brandon Little <blittle@inco.cc>
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

#include <vector>
#include <algorithm>
#include "RtMidi.h"
#include "GarrysMod/Lua/Interface.h"

using namespace std;
using namespace GarrysMod::Lua;

RtMidiIn* midiIn;
RtMidiOut* midiOut;

int IsPortOpen(ILuaBase* LUA, RtMidi* midi)
{
	try {
		LUA->PushBool(midi->isPortOpen());
	}
	catch (const RtMidiError& error) {
		LUA->ThrowError(error.what());
	}

	return 1;
}

int GetPortCount(ILuaBase* LUA, RtMidi* midi)
{
	try {
		LUA->PushNumber(midi->getPortCount());
	}
	catch (const RtMidiError& error) {
		LUA->ThrowError(error.what());
	}

	return 1;
}

int GetPortName(ILuaBase* LUA, RtMidi* midi)
{
	try {
		LUA->PushString(midi->getPortName(
		    (unsigned int)LUA->CheckNumber(1)).c_str());
	}
	catch (const RtMidiError& error) {
		LUA->ThrowError(error.what());
	}

	return 1;
}

int ClosePort(ILuaBase* LUA, RtMidi* midi,
    const char* preHook, const char* postHook)
{
	LUA->PushSpecial(SPECIAL_GLOB);
	LUA->GetField(-1, "hook");
	LUA->GetField(-1, "Run");
	LUA->PushString(preHook);
	LUA->Call(1, 1);

	const auto should = LUA->GetBool(-1) || LUA->IsType(-1, Type::Nil);

	if (should) {
		try {
			midi->closePort();
		}
		catch (const RtMidiError& error) {
			LUA->ThrowError(error.what());
		}

		LUA->GetField(-2, "Run");
		LUA->PushString(postHook);
		LUA->Call(1, 0);
	}

	LUA->PushBool(should);

	return 1;
}

int OpenPort(ILuaBase* LUA, RtMidi* midi,
    const char* preHook, const char* postHook)
{
	const auto port = (unsigned int)LUA->CheckNumber(1);

	LUA->PushSpecial(SPECIAL_GLOB);
	LUA->GetField(-1, "hook");
	LUA->GetField(-1, "Run");
	LUA->PushString(preHook);
	LUA->PushNumber(port);
	LUA->Call(2, 1);

	const auto should = LUA->GetBool(-1) || LUA->IsType(-1, Type::Nil);

	if (should) {
		try {
			midi->openPort(port);
		}
		catch (const RtMidiError& error) {
			LUA->ThrowError(error.what());
		}

		LUA->GetField(-2, "Run");
		LUA->PushString(postHook);
		LUA->PushNumber(port);
		LUA->Call(2, 0);
	}

	LUA->PushBool(should);

	return 1;
}

LUA_FUNCTION(IsInputPortOpen)
{
	return IsPortOpen(LUA, midiIn);
}

LUA_FUNCTION(GetInputPortCount)
{
	return GetPortCount(LUA, midiIn);
}

LUA_FUNCTION(GetInputPortName)
{
	return GetPortName(LUA, midiIn);
}

LUA_FUNCTION(OpenInputPort)
{
	return OpenPort(LUA, midiIn,
	    "ShouldOpenMIDIInputPort", "OnMIDIInputPortOpened");
}

LUA_FUNCTION(CloseInputPort)
{
	return ClosePort(LUA, midiIn,
	    "ShouldCloseMIDIInputPort", "OnMIDIInputPortClosed");
}

LUA_FUNCTION(IsOutputPortOpen)
{
	return IsPortOpen(LUA, midiOut);
}

LUA_FUNCTION(GetOutputPortCount)
{
	return GetPortCount(LUA, midiOut);
}

LUA_FUNCTION(GetOutputPortName)
{
	return GetPortName(LUA, midiOut);
}

LUA_FUNCTION(OpenOutputPort)
{
	return OpenPort(LUA, midiOut,
	    "ShouldOpenMIDIOutputPort", "OnMIDIOutputPortOpened");
}

LUA_FUNCTION(CloseOutputPort)
{
	return ClosePort(LUA, midiOut,
	    "ShouldCloseMIDIOutputPort", "OnMIDIOutputPortClosed");
}

LUA_FUNCTION(SendMessage)
{
	vector<unsigned char> message;

	for (int i = 1; i <= max(1, LUA->Top()); i++)
		message.push_back((unsigned char)LUA->CheckNumber(i));

	const auto size = (int)message.size();

	LUA->PushSpecial(SPECIAL_GLOB);
	LUA->GetField(-1, "hook");
	LUA->GetField(-1, "Run");
	LUA->PushString("ShouldSendMIDIMessage");

	for (const double byte : message)
		LUA->PushNumber(byte);

	LUA->Call(size + 1, 1);

	const auto should = LUA->GetBool(-1) || LUA->IsType(-1, Type::Nil);

	if (should) {
		try {
			midiOut->sendMessage(&message);
		}
		catch (const RtMidiError& error) {
			LUA->ThrowError(error.what());
		}

		LUA->GetField(-2, "Run");
		LUA->PushString("OnMIDIMessageSent");

		for (const double byte : message)
			LUA->PushNumber(byte);

		LUA->Call(size + 1, 0);
	}

	LUA->PushBool(should);

	return 1;
}

LUA_FUNCTION(ReceiveMessage)
{
	vector<unsigned char> message;

	try {
		midiIn->getMessage(&message);
	}
	catch (const RtMidiError& error) {
		LUA->ThrowError(error.what());
	}

	const auto size = (int)message.size();

	if (size > 0) {
		LUA->PushSpecial(SPECIAL_GLOB);
		LUA->GetField(-1, "hook");
		LUA->GetField(-1, "Run");
		LUA->PushString("ShouldReceiveMIDIMessage");

		for (const double byte : message)
			LUA->PushNumber(byte);

		LUA->Call(size + 1, 1);

		const auto should = LUA->GetBool(-1) || LUA->IsType(-1, Type::Nil);

		if (should) {
			LUA->GetField(-2, "Run");
			LUA->PushString("OnMIDIMessageReceived");

			for (const double byte : message)
				LUA->PushNumber(byte);

			LUA->Call(size + 1, 0);
		}

		for (const double byte : message)
			LUA->PushNumber(byte);
	}

	return size;
}

LUA_FUNCTION(Think)
{
	while (true) {
		LUA->PushCFunction(ReceiveMessage);
		LUA->Call(0, 1);

		if (LUA->IsType(-1, Type::Nil))
			break;
	}

	return 0;
}

GMOD_MODULE_OPEN()
{
	try {
		midiIn = new RtMidiIn();
		midiOut = new RtMidiOut();
	}
	catch(const RtMidiError& error) {
		LUA->ThrowError(error.what());
	}

	LUA->PushSpecial(SPECIAL_GLOB);
	LUA->CreateTable();
	LUA->PushCFunction(IsInputPortOpen);
	LUA->SetField(-2, "IsInputPortOpen");
	LUA->PushCFunction(GetInputPortCount);
	LUA->SetField(-2, "GetInputPortCount");
	LUA->PushCFunction(GetInputPortName);
	LUA->SetField(-2, "GetInputPortName");
	LUA->PushCFunction(OpenInputPort);
	LUA->SetField(-2, "OpenInputPort");
	LUA->PushCFunction(CloseInputPort);
	LUA->SetField(-2, "CloseInputPort");
	LUA->PushCFunction(IsOutputPortOpen);
	LUA->SetField(-2, "IsOutputPortOpen");
	LUA->PushCFunction(GetOutputPortCount);
	LUA->SetField(-2, "GetOutputPortCount");
	LUA->PushCFunction(GetOutputPortName);
	LUA->SetField(-2, "GetOutputPortName");
	LUA->PushCFunction(OpenOutputPort);
	LUA->SetField(-2, "OpenOutputPort");
	LUA->PushCFunction(CloseOutputPort);
	LUA->SetField(-2, "CloseOutputPort");
	LUA->PushCFunction(SendMessage);
	LUA->SetField(-2, "SendMessage");
	LUA->PushCFunction(ReceiveMessage);
	LUA->SetField(-2, "ReceiveMessage");
	LUA->SetField(-2, "rtmidi");
	LUA->GetField(-1, "hook");
	LUA->GetField(-1, "Add");
	LUA->PushString("Think");
	LUA->PushString("rtmidi");
	LUA->PushCFunction(Think);
	LUA->Call(3, 0);

	return 0;
}

GMOD_MODULE_CLOSE()
{
	try {
		delete midiIn;
		delete midiOut;
	}
	catch (const RtMidiError& error) {
		LUA->ThrowError(error.what());
	}

	LUA->PushSpecial(SPECIAL_GLOB);
	LUA->PushNil();
	LUA->SetField(-2, "rtmidi");
	LUA->GetField(-1, "hook");
	LUA->GetField(-1, "Remove");
	LUA->PushString("Think");
	LUA->PushString("rtmidi");
	LUA->Call(2, 0);

	return 0;
}
