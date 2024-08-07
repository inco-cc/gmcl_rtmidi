/* See LICENSE file for copyright and license details. */

#include <map>
#include "GarrysMod/Lua/Interface.h"

std::map<int, const char*> controlName {
    {   -1, "MIDI_CONTROL_UNDEFINED" },
    { 0x00, "MIDI_CONTROL_BANK_SELECT" },
    { 0x01, "MIDI_CONTROL_MODULATION_WHEEL" },
    { 0x02, "MIDI_CONTROL_BREATH_CONTROLLER" },
    { 0x04, "MIDI_CONTROL_FOOT_CONTROLLER" },
    { 0x05, "MIDI_CONTROL_PORTAMENTO_TIME" },
    { 0x06, "MIDI_CONTROL_DATA_ENTRY" },
    { 0x07, "MIDI_CONTROL_CHANNEL_VOLUME" },
    { 0x08, "MIDI_CONTROL_BALANCE" },
    { 0x0A, "MIDI_CONTROL_PAN" },
    { 0x0B, "MIDI_CONTROL_EXPRESSION_CONTROLLER" },
    { 0x0C, "MIDI_CONTROL_EFFECT_CONTROL_1" },
    { 0x0D, "MIDI_CONTROL_EFFECT_CONTROL_2" },
    { 0x10, "MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_1" },
    { 0x11, "MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_2" },
    { 0x12, "MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_3" },
    { 0x13, "MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_4" },
    { 0x40, "MIDI_CONTROL_DAMPER_PEDAL" },
    { 0x41, "MIDI_CONTROL_PORTAMENTO_TOGGLE" },
    { 0x42, "MIDI_CONTROL_SOSTENUTO" },
    { 0x43, "MIDI_CONTROL_SOFT_PEDAL" },
    { 0x44, "MIDI_CONTROL_LEGATO_FOOTSWITCH" },
    { 0x45, "MIDI_CONTROL_HOLD_2" },
    { 0x46, "MIDI_CONTROL_SOUND_CONTROLLER_1" },
    { 0x47, "MIDI_CONTROL_SOUND_CONTROLLER_2" },
    { 0x48, "MIDI_CONTROL_SOUND_CONTROLLER_3" },
    { 0x49, "MIDI_CONTROL_SOUND_CONTROLLER_4" },
    { 0x4A, "MIDI_CONTROL_SOUND_CONTROLLER_5" },
    { 0x4B, "MIDI_CONTROL_SOUND_CONTROLLER_6" },
    { 0x4C, "MIDI_CONTROL_SOUND_CONTROLLER_7" },
    { 0x4D, "MIDI_CONTROL_SOUND_CONTROLLER_8" },
    { 0x4E, "MIDI_CONTROL_SOUND_CONTROLLER_9" },
    { 0x4F, "MIDI_CONTROL_SOUND_CONTROLLER_10" },
    { 0x50, "MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_5" },
    { 0x51, "MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_6" },
    { 0x52, "MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_7" },
    { 0x53, "MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_8" },
    { 0x54, "MIDI_CONTROL_PORTAMENTO_CONTROL" },
    { 0x5B, "MIDI_CONTROL_EFFECTS_1_DEPTH" },
    { 0x5C, "MIDI_CONTROL_EFFECTS_2_DEPTH" },
    { 0x5D, "MIDI_CONTROL_EFFECTS_3_DEPTH" },
    { 0x5E, "MIDI_CONTROL_EFFECTS_4_DEPTH" },
    { 0x5F, "MIDI_CONTROL_EFFECTS_5_DEPTH" },
    { 0x60, "MIDI_CONTROL_DATA_INCREMENT" },
    { 0x61, "MIDI_CONTROL_DATA_DECREMENT" },
    { 0x62, "MIDI_CONTROL_NON_REGISTERED_PARAMETER_NUMBER" },
    { 0x64, "MIDI_CONTROL_REGISTERED_PARAMETER_NUMBER" },
};

LUA_FUNCTION(GetControlName)
{
    auto control = (int)LUA->CheckNumber(1);

    if (control >= 0x20 and control <= 0x3F)
        control -= 0x20;
    else if (control == 0x63 or control == 0x65)
        control -= 0x01;

    if (controlName.count(control) <= 0)
        control = -1;

    LUA->PushString(controlName.at(control));

    return 1;
}

LUA_FUNCTION(GetControlBitSignificance)
{
    const auto control = (int)LUA->CheckNumber(1);

    if (control >= 0x20 and control <= 0x3F)
        LUA->PushNumber(0);
    else if (control == 0x62 or control == 0x64)
        LUA->PushNumber(0);
    else
        LUA->PushNumber(1);

    return 1;
}
