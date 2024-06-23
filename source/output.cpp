/* See LICENSE file for copyright and license details. */

#include <map>
#include "RtMidi.h"
#include "GarrysMod/Lua/Interface.h"

RtMidiOut *mainOutput;

std::map<unsigned int, RtMidiOut*> portOutput;

LUA_FUNCTION(GetOutputPortCount)
{
    try {
        LUA->PushNumber(mainOutput->getPortCount());
    }
    catch (const RtMidiError &error) {
        LUA->ThrowError(error.what());
    }

    return 1;
}

LUA_FUNCTION(GetOutputPortName)
{
    try {
        LUA->PushString(mainOutput->getPortName(
            (unsigned int)LUA->CheckNumber(1)).c_str());
    }
    catch (const RtMidiError &error) {
        LUA->ThrowError(error.what());
    }

    return 1;
}

LUA_FUNCTION(IsOutputPortOpen)
{
    const auto port = (unsigned int)LUA->CheckNumber(1);

    try {
        LUA->PushBool(portOutput.count(port) > 0
            and portOutput.at(port)->isPortOpen());
    }
    catch (const RtMidiError &error) {
        LUA->ThrowError(error.what());
    }

    return 1;
}

LUA_FUNCTION(CloseOutputPort)
{
    const auto port = (unsigned int)LUA->CheckNumber(1);

    if (portOutput.count(port) > 0) {
        LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
        LUA->GetField(-1, "hook");
        LUA->GetField(-1, "Run");
        LUA->PushString("ShouldCloseMIDIOutputPort");
        LUA->PushNumber(port);
        LUA->Call(2, 1);

        if (LUA->GetBool(-1) or LUA->IsType(-1, GarrysMod::Lua::Type::Nil)) {
            auto output = portOutput.at(port);

            try {
                output->closePort();
            }
            catch (const RtMidiError &error) {
                LUA->ThrowError(error.what());
            }

            portOutput.erase(port);

            delete output;

            LUA->GetField(-2, "Run");
            LUA->PushString("OnMIDIOutputPortClosed");
            LUA->PushNumber(port);
            LUA->Call(2, 0);
            LUA->PushBool(true);

            return 1;
        }
    }

    LUA->PushBool(false);

    return 1;
}

LUA_FUNCTION(OpenOutputPort)
{
    const auto port = (unsigned int)LUA->CheckNumber(1);

    if (portOutput.count(port) < 1) {
        LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
        LUA->GetField(-1, "hook");
        LUA->GetField(-1, "Run");
        LUA->PushString("ShouldOpenMIDIOutputPort");
        LUA->PushNumber(port);
        LUA->Call(2, 1);

        if (LUA->GetBool(-1) or LUA->IsType(-1, GarrysMod::Lua::Type::Nil)) {
            auto output = new RtMidiOut();

            try {
                output->openPort(port);
            }
            catch (const RtMidiError &error) {
                LUA->ThrowError(error.what());
            }

            portOutput.emplace(port, output);

            LUA->GetField(-2, "Run");
            LUA->PushString("OnMIDIOutputPortOpened");
            LUA->PushNumber(port);
            LUA->Call(2, 0);
            LUA->PushBool(true);

            return 1;
        }
    }

    LUA->PushBool(false);

    return 1;
}

LUA_FUNCTION(SendMessage)
{
    const auto port = (unsigned int)LUA->CheckNumber(1);

    if (portOutput.count(port) > 0) {
        auto output = portOutput.at(port);

        std::vector<unsigned char> message;

        for (int i = 2; i < LUA->Top() + 1; i++) {
            message.push_back((unsigned char)LUA->CheckNumber(i));
        }

        const auto size = message.size();

        if (size > 0) {
            LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
            LUA->GetField(-1, "hook");
            LUA->GetField(-1, "Run");
            LUA->PushString("ShouldSendMIDIMessage");
            LUA->PushNumber(port);

            for (const auto byte : message) {
                LUA->PushNumber(byte);
            }

            LUA->Call(2 + size, 1);

            if (LUA->GetBool(-1) or LUA->IsType(-1, GarrysMod::Lua::Type::Nil)) {
                try {
                    output->sendMessage(&message);
                }
                catch (const RtMidiError &error) {
                    LUA->ThrowError(error.what());
                }

                LUA->GetField(-2, "Run");
                LUA->PushString("OnMIDIMessageSent");
                LUA->PushNumber(port);

                for (const double byte : message) {
                    LUA->PushNumber(byte);
                }

                LUA->Call(2 + size, 0);
                LUA->PushBool(true);

                return 1;
            }
        }
    }

    LUA->PushBool(false);

    return 1;
}
