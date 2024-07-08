# Changelog

All notable changes to this project are documented in this file.

## Upcoming

The following changes were made after the previous version, and will be available in the next version.

### Added

#### Functions

- rtmidi.GetMessageName
- rtmidi.GetMessageTypeName
- rtmidi.GetMessageType
- rtmidi.GetMessageChannel
- rtmidi.GetControlName
- rtmidi.GetControlBitSignificance

#### Enumerations

##### MIDI_MESSAGE

- MIDI_MESSAGE_UNDEFINED
- MIDI_MESSAGE_ALL_SOUND_OFF
- MIDI_MESSAGE_RESET_ALL_CONTROLLERS
- MIDI_MESSAGE_LOCAL_CONTROL
- MIDI_MESSAGE_ALL_NOTES_OFF
- MIDI_MESSAGE_OMNI_MODE_OFF
- MIDI_MESSAGE_OMNI_MODE_ON
- MIDI_MESSAGE_MONO_MODE_ON
- MIDI_MESSAGE_POLY_MODE_ON
- MIDI_MESSAGE_NOTE_OFF
- MIDI_MESSAGE_NOTE_ON
- MIDI_MESSAGE_POLYPHONIC_KEY_PRESSURE
- MIDI_MESSAGE_CONTROL_CHANGE
- MIDI_MESSAGE_PROGRAM_CHANGE
- MIDI_MESSAGE_CHANNEL_PRESSURE
- MIDI_MESSAGE_PITCH_BEND_CHANGE
- MIDI_MESSAGE_SOX
- MIDI_MESSAGE_MIDI_TIME_CODE_QUARTER_FRAME
- MIDI_MESSAGE_SONG_POSITION_POINTER
- MIDI_MESSAGE_SONG_SELECT
- MIDI_MESSAGE_TUNE_REQUEST
- MIDI_MESSAGE_EOX
- MIDI_MESSAGE_TIMING_CLOCK
- MIDI_MESSAGE_START
- MIDI_MESSAGE_CONTINUE
- MIDI_MESSAGE_STOP
- MIDI_MESSAGE_ACTIVE_SENSING
- MIDI_MESSAGE_SYSTEM_RESET

##### MIDI_MESSAGE_TYPE

- MIDI_MESSAGE_TYPE_UNDEFINED
- MIDI_MESSAGE_TYPE_CHANNEL_VOICE
- MIDI_MESSAGE_TYPE_CHANNEL_MODE
- MIDI_MESSAGE_TYPE_SYSTEM_COMMON
- MIDI_MESSAGE_TYPE_SYSTEM_REALTIME
- MIDI_MESSAGE_TYPE_SYSTEM_EXCLUSIVE

##### MIDI_CONTROL

- MIDI_CONTROL_UNDEFINED
- MIDI_CONTROL_BANK_SELECT
- MIDI_CONTROL_MODULATION_WHEEL
- MIDI_CONTROL_BREATH_CONTROLLER
- MIDI_CONTROL_FOOT_CONTROLLER
- MIDI_CONTROL_PORTAMENTO_TIME
- MIDI_CONTROL_DATA_ENTRY
- MIDI_CONTROL_CHANNEL_VOLUME
- MIDI_CONTROL_BALANCE
- MIDI_CONTROL_PAN
- MIDI_CONTROL_EXPRESSION_CONTROLLER
- MIDI_CONTROL_EFFECT_CONTROL_1
- MIDI_CONTROL_EFFECT_CONTROL_2
- MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_1
- MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_2
- MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_3
- MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_4
- MIDI_CONTROL_DAMPER_PEDAL
- MIDI_CONTROL_PORTAMENTO_TOGGLE
- MIDI_CONTROL_SOSTENUTO
- MIDI_CONTROL_SOFT_PEDAL
- MIDI_CONTROL_LEGATO_FOOTSWITCH
- MIDI_CONTROL_HOLD_2
- MIDI_CONTROL_SOUND_CONTROLLER_1
- MIDI_CONTROL_SOUND_CONTROLLER_2
- MIDI_CONTROL_SOUND_CONTROLLER_3
- MIDI_CONTROL_SOUND_CONTROLLER_4
- MIDI_CONTROL_SOUND_CONTROLLER_5
- MIDI_CONTROL_SOUND_CONTROLLER_6
- MIDI_CONTROL_SOUND_CONTROLLER_7
- MIDI_CONTROL_SOUND_CONTROLLER_8
- MIDI_CONTROL_SOUND_CONTROLLER_9
- MIDI_CONTROL_SOUND_CONTROLLER_10
- MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_5
- MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_6
- MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_7
- MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_8
- MIDI_CONTROL_PORTAMENTO_CONTROL
- MIDI_CONTROL_EFFECTS_1_DEPTH
- MIDI_CONTROL_EFFECTS_2_DEPTH
- MIDI_CONTROL_EFFECTS_3_DEPTH
- MIDI_CONTROL_EFFECTS_4_DEPTH
- MIDI_CONTROL_EFFECTS_5_DEPTH
- MIDI_CONTROL_DATA_INCREMENT
- MIDI_CONTROL_DATA_DECREMENT
- MIDI_CONTROL_NON_REGISTERED_PARAMETER_NUMBER
- MIDI_CONTROL_REGISTERED_PARAMETER_NUMBER

## 0.2.0

This version introduces output variants of the input functions and hooks that
were introduced in version `0.1.0`.

There is also a new autorun script to quickly test the module using console
commands with verbose output.

This version was released on June 27, 2024.

### Added

#### Files

- COMPILING.md
  - A supplementary guide on how to compile this project from source.
  - Still a work in progress, but it covers the essentials.
- rtmidi_test.lua
  - An autorun script to quickly test functions and hooks.
  - Drop in `lua/autorun/client` and run the `rtmidi_` console commands.
  - Hooks are created to print what is happening and the data being passed.

#### Functions

- rtmidi.GetOutputPortCount
- rtmidi.GetOutputPortName
- rtmidi.IsOutputPortOpen
- rtmidi.CloseOutputPort
- rtmidi.OpenOutputPort
- rtmidi.SendMessage

#### Hooks

- GM:ShouldCloseMIDIOutputPort
- GM:OnMIDIOutputPortClosed
- GM:ShouldOpenMIDIOutputPort
- GM:OnMIDIOutputPortOpened
- GM:ShouldSendMIDIMessage
- GM:OnMIDIMessageSent

## 0.1.0

This marks the very first version of the project!

This version introduces most of the essentials for realtime MIDI input in Lua.

The next version will focus on MIDI output.

This version was released on June 22, 2024.

### Added

#### Functions

- rtmidi.GetInputPortCount
- rtmidi.GetInputPortName
- rtmidi.IsInputPortOpen
- rtmidi.CloseInputPort
- rtmidi.OpenInputPort
- rtmidi.ReceiveMessage

#### Hooks

- GM:ShouldCloseMIDIInputPort
- GM:OnMIDIInputPortClosed
- GM:ShouldOpenMIDIInputPort
- GM:OnMIDIInputPortOpened
- GM:ShouldReceiveMIDIMessage
- GM:OnMIDIMessageReceived
