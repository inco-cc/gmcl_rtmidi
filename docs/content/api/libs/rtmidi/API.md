---
title: API
---

## Description

Enumerations used to specify backend MIDI APIs.

## Values

| Name          | Value | Description                                          |
|---------------|-------|------------------------------------------------------|
| UNSPECIFIED   | 0     | Select a supported API automatically
| MACOSX_CORE   | 1     | macOS Core MIDI
| LINUX_ALSA    | 2     | Advanced Linux Sound Architecture
| UNIX_JACK     | 3     | JACK Audio Connection Kit
| WINDOWS_MM    | 4     | Windows Multimedia
| RTMIDI_DUMMY  | 5     | Dummy API
| WEB_MIDI_API  | 6     | W3C Web MIDI
| WINDOWS_UWP   | 7     | Universal Windows Platform
| ANDROID_AMIDI | 8     | Android MIDI
| NUM_APIS      | 9     | Total number of APIs
