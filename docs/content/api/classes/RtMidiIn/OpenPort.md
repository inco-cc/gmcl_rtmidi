---
title: OpenPort
---

```lua
RtMidiIn:OpenPort(number port)
```

## Description

Opens a port to receive messages from.

Only one port can be open at a time per RtMidiIn instance.  
If you need to receive messages from multiple ports simultaneously, create another RtMidiIn instance with [rtmidi.CreateInput]({{% ref "api/libs/rtmidi/CreateInput" %}}).

## Arguments

1. [number](https://wiki.facepunch.com/gmod/number) port  
The port number.
