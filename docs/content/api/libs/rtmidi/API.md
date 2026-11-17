---
title: API
---

## Description

Enumerations for all the low-level MIDI APIs supported by RtMidi.

{{< note >}}
Availability of these APIs at runtime will depend on whether support was enabled for them during compilation.  
Use [rtmidi.GetCompiledAPI]({{% ref "api/libs/rtmidi/GetCompiledAPI" %}}) to return a list of available APIs at runtime.
{{< /note >}}

## Values

| Name                     | Value | Description                                          |
|--------------------------|-------|------------------------------------------------------|
| UNSPECIFIED              | 0     | Select a supported API automatically
| MACOSX_CORE              | 1     | macOS Core MIDI
| LINUX_ALSA               | 2     | Advanced Linux Sound Architecture
| UNIX_JACK                | 3     | JACK Audio Connection Kit
| WINDOWS_MM               | 4     | Windows Multimedia
| RTMIDI_DUMMY             | 5     | Dummy API
| WEB_MIDI_API             | 6     | W3C Web MIDI
| WINDOWS_UWP              | 7     | Universal Windows Platform
| ANDROID_AMIDI            | 8     | Android MIDI
| WINDOWS_MIDI_SERVICES    | 9     | Windows MIDI Services
| NUM_APIS                 | 10    | Total number of APIs
