---
title: SendMessage
---

```lua
RtMidiOut:SendMessage(...)
```

## Description

Sends a message to the port that is currently open.

Messages are only sent when a port is opened with [RtMidiOut:OpenPort]({{% ref "api/classes/RtMidiOut/OpenPort" %}}).

## Arguments

1. [vararg](https://wiki.facepunch.com/gmod/vararg)  
The message to send, as a sequence of bytes.  
The first byte represents the message status, potentially followed by data bytes.  
What each data byte represents will depend on what the status byte is.  
See the [MIDI 1.0 specification](https://archive.org/details/Complete_MIDI_1.0_Detailed_Specification_96-1-3) for more information.
