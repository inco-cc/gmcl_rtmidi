/* See LICENSE file for copyright and license details. */

#include "RtMidi.h"
#include "GarrysMod/Lua/Interface.h"
#include "input.h"

GMOD_MODULE_OPEN()
{
    try {
        mainInput = new RtMidiIn();
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
    LUA->SetField(-2, "rtmidi");

    return 0;
}

GMOD_MODULE_CLOSE()
{
    LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
    LUA->PushNil();
    LUA->SetField(-2, "rtmidi");

    delete mainInput;

    return 0;
}
