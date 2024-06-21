/* See LICENSE file for copyright and license details. */

#include <map>
#include "RtMidi.h"
#include "GarrysMod/Lua/Interface.h"

RtMidiIn *mainInput;

std::map<unsigned int, RtMidiIn*> portInput;

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

LUA_FUNCTION(IsInputPortOpen)
{
    const auto port = (unsigned int)LUA->CheckNumber(1);

    if (portInput.count(port) != 0) {
        const auto input = portInput.at(port);
        const auto open = input->isPortOpen();

        LUA->PushBool(open);

        if (not open) {
            portInput.erase(port);

            delete input;
        }
    }
    else {
        LUA->PushBool(false);
    }

    return 1;
}
