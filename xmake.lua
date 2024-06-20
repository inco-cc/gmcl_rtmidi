set_allowedmodes("debug", "release")
set_allowedplats("windows", "linux", "macosx")
set_allowedarchs(
    "windows|x86", "windows|x64",
    "linux|x86_64", "linux|i386",
    "macosx|x86_64")
add_languages("cxx14")

if is_plat("linux", "macosx") then
    add_cxflags("-fPIC")
end

if is_mode("release") then
    set_runtimes("MT")
    set_optimize("fastest")
    set_symbols("hidden")
    set_strip("all")
elseif is_mode("debug") then
    set_runtimes("MTd")
    set_optimize("none")
    set_symbols("debug")
end

target("rtmidi")
    set_kind("object")
    add_includedirs("thirdparty/rtmidi")
    add_files("thirdparty/rtmidi/RtMidi.cpp")
    add_defines("RTMIDI_DO_NOT_ENSURE_UNIQUE_PORTNAMES")

    if is_mode("debug") then
        add_defines("__RTMIDI_DEBUG__")
    end

    if is_plat("windows") then
        add_defines("__WINDOWS_MM__")
    elseif is_plat("linux") then
        add_defines("__LINUX_ALSA__")
    elseif is_plat("macosx") then
        add_defines("__MACOSX_CORE__")
    end

target("gmcl_rtmidi")
    set_default(true)
    set_kind("shared")
    set_prefixname("gmcl_")
    set_basename("rtmidi")
    set_extension(".dll")
    add_includedirs(
        "include",
        "thirdparty/rtmidi",
        "thirdparty/gmod-module-base/include")
    add_files("source/**.cpp")
    add_deps("rtmidi")

    if is_plat("windows") then
        add_syslinks("winmm")

        if is_arch("x64") then
            set_suffixname("_win64")
        elseif is_arch("x86") then
            set_suffixname("_win32")
        end
    elseif is_plat("linux") then
        add_syslinks("asound", "pthread")

        if is_arch("x86_64") then
            set_suffixname("_linux64")
        elseif is_arch("i386") then
            set_suffixname("_linux")
        end
    elseif is_plat("macosx") then
        add_frameworks("CoreMIDI", "CoreAudio", "CoreFoundation")

        if is_arch("x86_64") then
            set_suffixname("_osx")
        end
    end

