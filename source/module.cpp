/* See LICENSE file for copyright and license details. */

#include "RtMidi.h"
#include "GarrysMod/Lua/Interface.h"
#include "input.h"
#include "output.h"
#include "message.h"
#include "control.h"

GMOD_MODULE_OPEN()
{
    try {
        mainInput = new RtMidiIn();
        mainOutput = new RtMidiOut();
    }
    catch (const RtMidiError &error) {
        LUA->ThrowError(error.what());
    }

    LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
    LUA->CreateTable();
    LUA->PushCFunction(&GetInputPortCount);
    LUA->SetField(-2, "GetInputPortCount");
    LUA->PushCFunction(&GetInputPortName);
    LUA->SetField(-2, "GetInputPortName");
    LUA->PushCFunction(&IsInputPortOpen);
    LUA->SetField(-2, "IsInputPortOpen");
    LUA->PushCFunction(&CloseInputPort);
    LUA->SetField(-2, "CloseInputPort");
    LUA->PushCFunction(&OpenInputPort);
    LUA->SetField(-2, "OpenInputPort");
    LUA->PushCFunction(&ReceiveMessage);
    LUA->SetField(-2, "ReceiveMessage");
    LUA->PushCFunction(&GetOutputPortCount);
    LUA->SetField(-2, "GetOutputPortCount");
    LUA->PushCFunction(&GetOutputPortName);
    LUA->SetField(-2, "GetOutputPortName");
    LUA->PushCFunction(&IsOutputPortOpen);
    LUA->SetField(-2, "IsOutputPortOpen");
    LUA->PushCFunction(&CloseOutputPort);
    LUA->SetField(-2, "CloseOutputPort");
    LUA->PushCFunction(&OpenOutputPort);
    LUA->SetField(-2, "OpenOutputPort");
    LUA->PushCFunction(&SendMessage);
    LUA->SetField(-2, "SendMessage");
    LUA->PushCFunction(&GetMessageName);
    LUA->SetField(-2, "GetMessageName");
    LUA->PushCFunction(&GetMessageTypeName);
    LUA->SetField(-2, "GetMessageTypeName");
    LUA->PushCFunction(&GetMessageType);
    LUA->SetField(-2, "GetMessageType");
    LUA->PushCFunction(&GetControlName);
    LUA->SetField(-2, "GetControlName");
    LUA->SetField(-2, "rtmidi");

    for (const auto &pair : messageName) {
        LUA->PushNumber(pair.first);
        LUA->SetField(-2, pair.second);
    }

    for (const auto &pair : messageTypeName) {
        LUA->PushNumber(pair.first);
        LUA->SetField(-2, pair.second);
    }

    for (const auto &pair : controlName) {
        LUA->PushNumber(pair.first);
        LUA->SetField(-2, pair.second);
    }

    return 0;
}

GMOD_MODULE_CLOSE()
{
    LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
    LUA->PushNil();
    LUA->SetField(-2, "rtmidi");

    for (const auto &pair : messageName) {
        LUA->PushNil();
        LUA->SetField(-2, pair.second);
    }

    for (const auto &pair : messageTypeName) {
        LUA->PushNil();
        LUA->SetField(-2, pair.second);
    }

    for (const auto &pair : controlName) {
        LUA->PushNil();
        LUA->SetField(-2, pair.second);
    }

    try {
        delete mainInput;
        delete mainOutput;
    }
    catch (const RtMidiError &error) {
        LUA->ThrowError(error.what());
    }

    for (auto it = portInput.begin(); it != portInput.end(); ) {
        try {
            delete it->second;
        }
        catch (const RtMidiError &error) {
            LUA->ThrowError(error.what());
        }

        it = portInput.erase(it);
    }

    for (auto it = portOutput.begin(); it != portOutput.end(); ) {
        try {
            delete it->second;
        }
        catch (const RtMidiError &error) {
            LUA->ThrowError(error.what());
        }

        it = portOutput.erase(it);
    }

    return 0;
}
