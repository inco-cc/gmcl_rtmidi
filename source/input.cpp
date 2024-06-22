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

LUA_FUNCTION(CloseInputPort)
{
    const auto port = (unsigned int)LUA->CheckNumber(1);

    LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
    LUA->GetField(-1, "hook");
    LUA->GetField(-1, "Run");
    LUA->PushString("ShouldCloseMIDIInputPort");
    LUA->PushNumber(port);
    LUA->Call(2, 1);

    const auto should = LUA->GetBool(-1) or LUA->IsType(-1, GarrysMod::Lua::Type::Nil);

    if (should and portInput.count(port) != 0) {
        const auto input = portInput.at(port);
        const auto open = input->isPortOpen();

        LUA->PushBool(open);

        if (open) {
            try {
                input->closePort();
            }
            catch (RtMidiError &error) {
                LUA->ThrowError(error.what());
            }

            portInput.erase(port);

            delete input;
        }

        LUA->GetField(-2, "Run");
        LUA->PushString("OnMIDIInputPortClosed");
        LUA->PushNumber(port);
        LUA->Call(2, 0);
    }
    else {
        LUA->PushBool(false);
    }

    return 1;
}
