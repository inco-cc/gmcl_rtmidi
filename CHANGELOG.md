# Changelog

All notable changes to this project are documented in this file.

## Upcoming

The following changes were made after the previous version, and will be available in the next version.

### Added

- rtmidi.GetMessageName

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

## 0.2.0

This version introduces output variants of the input functions and hooks that
were introduced in version `0.1.0`.

There is also a new autorun script to quickly test the module using console
commands with verbose output.

This version was released on June 27, 2024.

### Added

- COMPILE.md
  - A supplementary guide on how to compile this project from source.
  - Still a work in progress, but it covers the essentials.

- rtmidi_test.lua
  - An autorun script to quickly test functions and hooks.
  - Drop in `lua/autorun/client` and run the `rtmidi_` console commands.
  - Hooks are created to print what is happening and the data being passed.

- rtmidi.GetOutputPortCount
- rtmidi.GetOutputPortName
- rtmidi.IsOutputPortOpen
- rtmidi.CloseOutputPort
- rtmidi.OpenOutputPort
- rtmidi.SendMessage

- GM:ShouldCloseMIDIOutputPort
- GM:OnMIDIOutputPortClosed
- GM:ShouldOpenMIDIOutputPort
- GM:OnMIDIOutputPortOpened
- GM:ShouldSendMIDIMessage
- GM:OnMIDIMessageSent

## 0.1.0

This marks the very first version of the project!

This version introduces most of the essentials for real-time MIDI input in Lua.

The next version will focus on MIDI output.

This version was released on June 22, 2024.

### Added

- rtmidi.GetInputPortCount
- rtmidi.GetInputPortName
- rtmidi.IsInputPortOpen
- rtmidi.CloseInputPort
- rtmidi.OpenInputPort
- rtmidi.ReceiveMessage

- GM:ShouldCloseMIDIInputPort
- GM:OnMIDIInputPortClosed
- GM:ShouldOpenMIDIInputPort
- GM:OnMIDIInputPortOpened
- GM:ShouldReceiveMIDIMessage
- GM:OnMIDIMessageReceived
