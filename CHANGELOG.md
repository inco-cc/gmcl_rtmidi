# Changelog

All notable changes to this project are documented in this file.

## Upcoming

The following changes were made after the previous version, and will be available in the next version.

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
