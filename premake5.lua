workspace "gmcl_rtmidi"
	startproject "gmcl_rtmidi"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"
	location("build/" .. os.target() .. "/" .. (_ACTION or ""))
	includedirs { "include" }
	configurations { "Debug", "Release" }

	filter "system:macosx"
		platforms { "x86_64" }
	filter "system:not macosx"
		platforms { "x86", "x86_64" }

	filter "platforms:x86"
		architecture "x86"
	filter "platforms:x86_64"
		architecture "x86_64"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		assemblydebug "On"
		defines { "DEBUG" }
	filter "configurations:Release"
		runtime "Release"
		symbols "Off"
		assemblydebug "Off"
		defines { "NDEBUG" }

newoption {
	trigger        = "with-jack",
	description    = "Build with JACK support",
	category       = "RtMidi",
}

project "gmcl_rtmidi"
	kind "SharedLib"
	files { "include/gmcl_rtmidi/**.hpp", "src/gmcl_rtmidi/**.cpp" }
	vpaths { ["Sources/*"] = { "include/gmcl_rtmidi/**.hpp", "src/gmcl_rtmidi/**.cpp" } }
	links { "rtmidi" }

	filter { "system:windows", "platforms:x86" }
		targetsuffix "_win32"
	filter { "system:windows", "platforms:x86_64" }
		targetsuffix "_win64"
	filter { "system:linux", "platforms:x86" }
		targetsuffix "_linux"
	filter { "system:linux", "platforms:x86_64" }
		targetsuffix "_linux64"
	filter { "system:macosx" }
		targetsuffix "_osx"

project "rtmidi"
	kind "StaticLib"
	files { "include/RtMidi.h", "src/RtMidi.cpp" }
	vpaths { ["Sources/*"] = { "include/*.h", "src/*.cpp" } }
	defines { "RTMIDI_DO_NOT_ENSURE_UNIQUE_PORTNAMES" }

	filter "configurations:Debug"
		defines { "__RTMIDI_DEBUG__" }

	filter "system:windows"
		defines { "__WINDOWS_MM__" }
		links { "winmm" }
	filter "system:linux"
		defines { "__LINUX_ALSA__" }
		links { "asound", "pthread" }
	filter "system:macosx"
		defines { "__MACOSX_CORE__" }
		links { "CoreMIDI.framework", "CoreAudio.framework", "CoreFoundation.framework" }
	filter "options:with-jack"
		defines { "__UNIX_JACK__" }
