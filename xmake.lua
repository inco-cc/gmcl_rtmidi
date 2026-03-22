set_allowedmodes("debug", "release")
set_allowedplats("windows", "mingw", "msys", "linux", "macosx")
set_allowedarchs(
	"windows|x86", "windows|x64",
	"mingw|i386", "mingw|x86_64",
	"msys|i386", "msys|x86_64",
	"linux|i386", "linux|x86_64",
	"macosx|x86_64"
)
set_defaultmode("debug")
set_defaultarchs("windows|x86", "mingw|i386", "msys|i386", "linux|i386")
add_languages("cxx14")
add_includedirs("include")

if is_mode("debug") then
	set_runtimes("MTd")
	set_symbols("debug")
	set_optimize("none")
else
	set_runtimes("MT")
	set_symbols("hidden")
	set_optimize("faster")
	set_strip("all")
end

target("gmcl_rtmidi")
	set_kind("shared")
	set_default(true)
	set_prefixname("gmcl_")
	set_basename("rtmidi")
	set_extension(".dll")
	add_files("src/gmcl_rtmidi/**.cpp")
	add_headerfiles("include/gmcl_rtmidi/**.h")
	add_deps("rtmidi")

	if is_plat("windows", "mingw", "msys") then
		if is_arch("x86", "i386") then
			set_suffixname("_win32")
		else
			set_suffixname("_win64")
		end
	elseif is_plat("linux") then
		if is_arch("x86", "i386") then
			set_suffixname("_linux")
		else
			set_suffixname("_linux64")
		end
	else
		set_suffixname("_osx")
	end

target("rtmidi")
	set_kind("static")
	add_files("src/RtMidi.cpp")
	add_headerfiles("include/RtMidi.h")

	if is_mode("debug") then
		add_defines("__RTMIDI_DEBUG__")
	end

	if is_plat("windows", "mingw", "msys") then
		add_defines("__WINDOWS_MM__")
		add_syslinks("winmm")
	elseif is_plat("linux") then
		add_defines("__LINUX_ALSA__")
		add_syslinks("asound", "pthread")
	else
		add_defines("__MACOSX_CORE__")
		add_frameworks("CoreMIDI", "CoreAudio", "CoreFoundation")
	end
