---
title: RtMidiInMessage
---

## Description

Table structure containing a realtime MIDI input message.

## Members

[number](https://wiki.facepunch.com/gmod/number) `timestamp`  
The number of seconds that have passed since the last message was received.  
This will be `0` for the very first message received, or when calling [RtMidiIn:GetMessage]({{% ref "api/classes/RtMidiIn/GetMessage" %}}) when there are no messages in the queue.

[table](https://wiki.facepunch.com/gmod/number) `message`  
The message, as a table of bytes.  
This will be empty when calling [RtMidiIn:GetMessage]({{% ref "api/classes/RtMidiIn/GetMessage" %}}) when there are no messages in the queue.  
The first byte represents the message status, potentially followed by data bytes.  
What each data byte represents will depend on what the status byte is.  
See the [MIDI 1.0 specification](https://archive.org/details/Complete_MIDI_1.0_Detailed_Specification_96-1-3) for more information.
