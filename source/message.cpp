/* See LICENSE file for copyright and license details. */

#include <map>
#include <cmath>
#include "GarrysMod/Lua/Interface.h"

std::map<int, const char*> messageName {
    {   -1, "MIDI_MESSAGE_UNDEFINED" },
    { 0x78, "MIDI_MESSAGE_ALL_SOUND_OFF" },
    { 0x79, "MIDI_MESSAGE_RESET_ALL_CONTROLLERS" },
    { 0x7A, "MIDI_MESSAGE_LOCAL_CONTROL" },
    { 0x7B, "MIDI_MESSAGE_ALL_NOTES_OFF" },
    { 0x7C, "MIDI_MESSAGE_OMNI_MODE_OFF" },
    { 0x7D, "MIDI_MESSAGE_OMNI_MODE_ON" },
    { 0x7E, "MIDI_MESSAGE_MONO_MODE_ON" },
    { 0x7F, "MIDI_MESSAGE_POLY_MODE_ON" },
    { 0x80, "MIDI_MESSAGE_NOTE_OFF" },
    { 0x90, "MIDI_MESSAGE_NOTE_ON" },
    { 0xA0, "MIDI_MESSAGE_POLYPHONIC_KEY_PRESSURE" },
    { 0xB0, "MIDI_MESSAGE_CONTROL_CHANGE" },
    { 0xC0, "MIDI_MESSAGE_PROGRAM_CHANGE" },
    { 0xD0, "MIDI_MESSAGE_CHANNEL_PRESSURE" },
    { 0xE0, "MIDI_MESSAGE_PITCH_BEND_CHANGE" },
    { 0xF0, "MIDI_MESSAGE_SOX" },
    { 0xF1, "MIDI_MESSAGE_MIDI_TIME_CODE_QUARTER_FRAME"},
    { 0xF2, "MIDI_MESSAGE_SONG_POSITION_POINTER" },
    { 0xF3, "MIDI_MESSAGE_SONG_SELECT" },
    { 0xF6, "MIDI_MESSAGE_TUNE_REQUEST" },
    { 0xF7, "MIDI_MESSAGE_EOX" },
    { 0xF8, "MIDI_MESSAGE_TIMING_CLOCK" },
    { 0xFA, "MIDI_MESSAGE_START" },
    { 0xFB, "MIDI_MESSAGE_CONTINUE" },
    { 0xFC, "MIDI_MESSAGE_STOP" },
    { 0xFE, "MIDI_MESSAGE_ACTIVE_SENSING" },
    { 0xFF, "MIDI_MESSAGE_SYSTEM_RESET" },
};

std::map<int, const char*> messageTypeName {
    { -1, "MIDI_MESSAGE_TYPE_UNDEFINED" },
    {  0, "MIDI_MESSAGE_TYPE_CHANNEL_VOICE" },
    {  1, "MIDI_MESSAGE_TYPE_CHANNEL_MODE" },
    {  2, "MIDI_MESSAGE_TYPE_SYSTEM_COMMON" },
    {  3, "MIDI_MESSAGE_TYPE_SYSTEM_REALTIME" },
    {  4, "MIDI_MESSAGE_TYPE_SYSTEM_EXCLUSIVE" },
};

LUA_FUNCTION(GetMessageName)
{
    auto message = (int)LUA->CheckNumber(1);

    if (message >= 0x80 and message <= 0xEF)
        message = 0x80 + std::floor((message - 0x80) / 16) * 16;

    if (messageName.count(message) <= 0)
        message = -1;

    LUA->PushString(messageName.at(message));

    return 1;
}

LUA_FUNCTION(GetMessageTypeName)
{
    auto messageType = (int)LUA->CheckNumber(1);

    if (messageTypeName.count(messageType) <= 0)
        messageType = -1;

    LUA->PushString(messageTypeName.at(messageType));

    return 1;
}

LUA_FUNCTION(GetMessageType)
{
    const auto message = (int)LUA->CheckNumber(1);

    if (message >= 0x80 and message <= 0xEF)
        LUA->PushNumber(0);
    else if (message >= 120 and message <= 127)
        LUA->PushNumber(1);
    else if (message >= 0xF1 and message <= 0xF7)
        LUA->PushNumber(2);
    else if (message >= 0xF8 and message <= 0xFF)
        LUA->PushNumber(3);
    else if (message == 0xF0)
        LUA->PushNumber(4);
    else
        LUA->PushNumber(-1);

    return 1;
}

LUA_FUNCTION(GetMessageChannel)
{
    const auto message = (int)LUA->CheckNumber(1);

    if (message >= 0x80 and message <= 0xEF)
        LUA->PushNumber(message % 16);
    else
        LUA->PushNumber(-1);

    return 1;
}
