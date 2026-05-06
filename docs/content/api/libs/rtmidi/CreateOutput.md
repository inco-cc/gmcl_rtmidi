---
title: CreateOutput
---

```lua
RtMidiOut rtmidi.CreateOutput(number api = rtmidi.API.UNSPECIFIED, string client_name = "Garry's Mod Output Client")
```

## Description

Creates a new instance of the [RtMidiOut]({{% ref "api/classes/RtMidiOut" %}}) class.

## Arguments

1. [number](https://wiki.facepunch.com/gmod/number) `api = rtmidi.API.UNSPECIFIED`  
The MIDI API to use. See the [rtmidi.API]({{% ref "api/libs/rtmidi/API" %}}) enumerations.  
The default value, `rtmidi.API.UNSPECIFIED`, will choose a supported API automatically.  
Specifying this argument is only useful when using an alternative API (e.g. JACK)
2. [string](https://wiki.facepunch.com/gmod/string) `client_name = "Garry's Mod Input Client"`  
The name of the MIDI client.

## Returns

1. [RtMidiOut]({{% ref "api/classes/RtMidiOut" %}})  
The created RtMidiOut instance.
