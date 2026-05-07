---
title: OpenPort
---

```lua
RtMidiOut:OpenPort(number port)
```

## Description

Opens a port to send messages to.

Only one port can be open at a time per RtMidiOut instance.  
If you need to send messages to multiple ports simultaneously, create another RtMidiOut instance with [rtmidi.CreateOutput]({{% ref "api/libs/rtmidi/CreateOutput" %}}).

## Arguments

1. [number](https://wiki.facepunch.com/gmod/number) port  
The port number.
