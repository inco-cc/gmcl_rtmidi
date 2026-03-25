solution "gmcl_rtmidi"
	startproject "gmcl_rtmidi"
	language "C++"
	location "build"
	flags { "Cpp20" }
	includedirs { "include" }
	platforms { "x32", "x64" }
	configurations { "Debug", "Release" }

	configuration "Debug"
		defines { "DEBUG" }
		flags { "ExtraWarnings", "Symbols", "FullSymbols" }
	configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize" }

	configuration { "Debug", "x32" }
		targetdir "build/bin/x32/Debug"
	configuration { "Debug", "x64" }
		targetdir "build/bin/x64/Debug"
	configuration { "Release", "x32" }
		targetdir "build/bin/x32/Release"
	configuration { "Release", "x64" }
		targetdir "build/bin/x64/Release"

project "gmcl_rtmidi"
	kind "SharedLib"
	flags { "StaticRuntime" }
	files { "include/gmcl_rtmidi/**.hpp", "src/gmcl_rtmidi/**.cpp" }
	vpaths { ["Sources/*"] = { "include/gmcl_rtmidi/**.hpp", "src/gmcl_rtmidi/**.cpp" } }
	links { "rtmidi" }

	configuration { "windows", "x32" }
		targetsuffix "_win32"
	configuration { "windows", "x64" }
		targetsuffix "_win64"
	configuration { "linux", "x32" }
		targetsuffix "_linux"
	configuration { "linux", "x64" }
		targetsuffix "_linux64"
	configuration "macosx"
		targetsuffix "_osx"
	configuration "linux or macosx"
		targetextension ".dll"

project "rtmidi"
	kind "StaticLib"
	files { "include/RtMidi.h", "src/RtMidi.cpp" }
	vpaths { ["Sources/*"] = { "include/*.h", "src/*.cpp" } }

	configuration "Debug"
		defines { "__RTMIDI_DEBUG__" }

	configuration "windows"
		defines { "__WINDOWS_MM__" }
		links { "winmm" }
	configuration "linux"
		defines { "__LINUX_ALSA__" }
		links { "asound", "pthread" }
	configuration "macosx"
		defines { "__MACOSX_CORE__" }
		links { "CoreMIDI.framework", "CoreAudio.framework", "CoreFoundation.framework" }
