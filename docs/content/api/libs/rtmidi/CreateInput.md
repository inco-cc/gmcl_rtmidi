---
title: CreateInput
---

```lua
RtMidiIn rtmidi.CreateInput(number api = rtmidi.API.UNSPECIFIED, string client_name = "Garry's Mod Input Client", number queue_size = 100)
```

## Description

Creates a new instance of the [RtMidiIn]({{% ref "api/classes/RtMidiIn" %}}) class.

## Arguments

1. [number](https://wiki.facepunch.com/gmod/number) `api = rtmidi.API.UNSPECIFIED`  
The MIDI API to use. See the [rtmidi.API]({{% ref "api/libs/rtmidi/API" %}}) enumerations.  
The default value, `rtmidi.API.UNSPECIFIED`, will choose a supported API automatically.  
Specifying this argument is only useful when using an alternative API (e.g. JACK)
2. [string](https://wiki.facepunch.com/gmod/string) `client_name = "Garry's Mod Input Client"`  
The name of the MIDI client.
3. [number](https://wiki.facepunch.com/gmod/number) `queue_size = 100`  
The maximum number of received messages to store in memory.  
Once this limit is reached, the oldest message in the queue will be discarded to make space for new messages.

## Returns

1. [RtMidiIn]({{% ref "api/classes/RtMidiIn" %}})  
The created RtMidiIn instance.
