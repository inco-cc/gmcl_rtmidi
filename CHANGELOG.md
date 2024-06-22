# Change Log

All notable changes to this project are documented in this file.

## Upcoming

The following changes were made after the previous version, and will be available in the next version.

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
