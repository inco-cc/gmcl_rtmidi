/* See LICENSE file for copyright and license details. */

#include "RtMidi.h"
#include "GarrysMod/Lua/Interface.h"

RtMidiIn *mainInput;

LUA_FUNCTION(GetInputPortCount)
{
    try {
        LUA->PushNumber(mainInput->getPortCount());
    }
    catch (RtMidiError &error) {
        LUA->ThrowError(error.what());
    }

    return 1;
}

LUA_FUNCTION(GetInputPortName)
{
    try {
        LUA->PushString(mainInput->getPortName(
            (unsigned int)LUA->CheckNumber(1)).c_str());
    }
    catch (RtMidiError &error) {
        LUA->ThrowError(error.what());
    }

    return 1;
}
