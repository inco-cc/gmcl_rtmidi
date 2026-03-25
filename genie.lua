solution "gmcl_rtmidi"
	startproject "gmcl_rtmidi"
	language "C++"
	location "build"
	includedirs { "include" }
	flags { "Cpp20", "StaticRuntime" }
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
	files { "include/gmcl_rtmidi/**.hpp", "src/gmcl_rtmidi/**.cpp" }
	vpaths { ["Sources/*"] = { "include/gmcl_rtmidi/**.hpp", "src/gmcl_rtmidi/**.cpp" } }
	links { "rtmidi" }

	configuration "linux or macosx"
		targetextension ".dll"

	configuration { "windows", "x32" }
		targetsuffix "_win32"
	configuration { "windows", "x64" }
		targetsuffix "_win64"
	configuration { "linux", "x32" }
		targetsuffix "_linux"
	configuration { "linux", "x64" }
		targetsuffix "_linux64"
	configuration { "macosx", "x64" }
		targetsuffix "_osx"

	configuration "windows"	
		links { "winmm" }
	configuration "linux"
		links { "asound", "pthread" }
	configuration "macosx"
		links { "CoreMIDI.framework", "CoreAudio.framework", "CoreFoundation.framework" }

project "rtmidi"
	kind "StaticLib"
	files { "include/RtMidi.h", "src/RtMidi.cpp" }
	vpaths { ["Sources/*"] = { "include/*.h", "src/*.cpp" } }

	configuration "Debug"
		defines { "__RTMIDI_DEBUG__" }

	configuration "windows"
		defines { "__WINDOWS_MM__" }
	configuration "linux"
		defines { "__LINUX_ALSA__" }
	configuration "macosx"
		defines { "__MACOSX_CORE__" }
