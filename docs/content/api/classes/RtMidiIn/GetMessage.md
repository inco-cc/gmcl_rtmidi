---
title: GetMessage
---

```lua
table RtMidiIn:GetMessage()
```

## Description

Returns the last received message and pops it from the queue.

{{< note >}}
Messages are only received when a port is opened with [RtMidiIn:OpenPort]({{% ref "api/classes/RtMidiIn/OpenPort" %}}).
{{< /note >}}

## Returns

1. [table](https://wiki.facepunch.com/gmod/table)  
The message data. See the [RtMidiInMessage]({{% ref "api/structs/RtMidiInMessage" %}}) struct.
