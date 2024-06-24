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
    catch (const RtMidiError &error) {
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
    catch (const RtMidiError &error) {
        LUA->ThrowError(error.what());
    }

    return 1;
}

LUA_FUNCTION(IsInputPortOpen)
{
    const auto port = (unsigned int)LUA->CheckNumber(1);

    try {
        LUA->PushBool(portInput.count(port) > 0
            and portInput.at(port)->isPortOpen());
    }
    catch (const RtMidiError &error) {
        LUA->ThrowError(error.what());
    }

    return 1;
}

LUA_FUNCTION(CloseInputPort)
{
    const auto port = (unsigned int)LUA->CheckNumber(1);

    if (portInput.count(port) > 0) {
        LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
        LUA->GetField(-1, "hook");
        LUA->GetField(-1, "Run");
        LUA->PushString("ShouldCloseMIDIInputPort");
        LUA->PushNumber(port);
        LUA->Call(2, 1);

        if (LUA->GetBool(-1) or LUA->IsType(-1, GarrysMod::Lua::Type::Nil)) {
            auto input = portInput.at(port);

            try {
                input->closePort();
            }
            catch (const RtMidiError &error) {
                LUA->ThrowError(error.what());
            }

            std::vector<unsigned char> message;

            while (message.size() > 0)
                try {
                    input->getMessage(&message);
                }
                catch (const RtMidiError &error) {
                    LUA->ThrowError(error.what());
                }

            portInput.erase(port);

            delete input;

            LUA->GetField(-2, "Run");
            LUA->PushString("OnMIDIInputPortClosed");
            LUA->PushNumber(port);
            LUA->Call(2, 0);
            LUA->PushBool(true);

            return 1;
        }
    }

    LUA->PushBool(false);

    return 1;
}

LUA_FUNCTION(OpenInputPort)
{
    const auto port = (unsigned int)LUA->CheckNumber(1);

    if (portInput.count(port) < 1) {
        LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
        LUA->GetField(-1, "hook");
        LUA->GetField(-1, "Run");
        LUA->PushString("ShouldOpenMIDIInputPort");
        LUA->PushNumber(port);
        LUA->Call(2, 1);

        if (LUA->GetBool(-1) or LUA->IsType(-1, GarrysMod::Lua::Type::Nil)) {
            auto input = new RtMidiIn();

            try {
                input->openPort(port);
            }
            catch (const RtMidiError &error) {
                LUA->ThrowError(error.what());
            }

            std::vector<unsigned char> message;

            while (message.size() > 0) {
                try {
                    input->getMessage(&message);
                }
                catch (const RtMidiError& error) {
                    LUA->ThrowError(error.what());
                }
            }

            portInput.emplace(port, input);

            LUA->GetField(-2, "Run");
            LUA->PushString("OnMIDIInputPortOpened");
            LUA->PushNumber(port);
            LUA->Call(2, 0);
            LUA->PushBool(true);

            return 1;
        }
    }

    LUA->PushBool(false);

    return 1;
}

LUA_FUNCTION(ReceiveMessage)
{
    const auto port = (unsigned int)LUA->CheckNumber(1);

    if (portInput.count(port) > 0) {
        auto input = portInput.at(port);

        double deltaTime; std::vector<unsigned char> message;

        try {
            deltaTime = input->getMessage(&message);
        }
        catch (const RtMidiError &error) {
            LUA->ThrowError(error.what());
        }

        const auto size = message.size();

        if (size > 0) {
            LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
            LUA->GetField(-1, "hook");
            LUA->GetField(-1, "Run");
            LUA->PushString("ShouldReceiveMIDIMessage");
            LUA->PushNumber(port);
            LUA->PushNumber(deltaTime);

            for (const auto byte : message)
                LUA->PushNumber(byte);

            LUA->Call(3 + size, 1);

            if (LUA->GetBool(-1) or LUA->IsType(-1, GarrysMod::Lua::Type::Nil)) {
                LUA->GetField(-2, "Run");
                LUA->PushString("OnMIDIMessageReceived");
                LUA->PushNumber(port);
                LUA->PushNumber(deltaTime);

                for (const double byte : message)
                    LUA->PushNumber(byte);

                LUA->Call(3 + size, 0);
                LUA->PushBool(true);

                return 1;
            }
        }
    }

    LUA->PushBool(false);

    return 1;
}
