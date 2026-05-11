cmake_minimum_required(VERSION 3.22..4.2.0 FATAL_ERROR)
project(gmcl_rtmidi
  VERSION 0.1.0
  DESCRIPTION "Realtime MIDI for Garry's Mod"
  LANGUAGES CXX
  HOMEPAGE_URL "https://github.com/inco-cc/gmcl_rtmidi"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(RTMIDI_BUILD_TESTING OFF)
set(RTMIDI_BUILD_STATIC_LIBS ON)

add_subdirectory(thirdparty/gmod-module-base/include)
add_subdirectory(thirdparty/rtmidi)

target_compile_definitions(rtmidi PUBLIC RTMIDI_DO_NOT_ENSURE_UNIQUE_PORTNAMES)

set(SOURCE_FILES
  src/classes/RtMidiIn.cpp
  src/classes/RtMidiOut.cpp
  src/libraries/rtmidi.cpp
  src/main.cpp
)
set(HEADER_FILES
  include/gmcl_rtmidi/classes/RtMidi.hpp
  include/gmcl_rtmidi/classes/RtMidiIn.hpp
  include/gmcl_rtmidi/classes/RtMidiOut.hpp
  include/gmcl_rtmidi/libraries/rtmidi.hpp
  include/gmcl_rtmidi/common.hpp
)

add_library(gmcl_rtmidi SHARED ${SOURCE_FILES} ${HEADER_FILES})

source_group(TREE ${CMAKE_SOURCE_DIR}/src PREFIX "Source Files" FILES ${SOURCE_FILES})
source_group(TREE ${CMAKE_SOURCE_DIR}/include/gmcl_rtmidi PREFIX "Header Files" FILES ${HEADER_FILES})

target_include_directories(gmcl_rtmidi PRIVATE include)
target_link_libraries(gmcl_rtmidi PRIVATE gmod-module-base rtmidi)

set_target_properties(gmcl_rtmidi PROPERTIES PREFIX "")
if(APPLE)
  set_target_properties(gmcl_rtmidi PROPERTIES SUFFIX "_osx.dll")
elseif(UNIX)
  if(${CMAKE_SIZEOF_VOID_P} STREQUAL "4")
    set_target_properties(gmcl_rtmidi PROPERTIES SUFFIX "_linux.dll")
  else()
    set_target_properties(gmcl_rtmidi PROPERTIES SUFFIX "_linux64.dll")
  endif()
elseif(WIN32)
  if(${CMAKE_SIZEOF_VOID_P} STREQUAL "4")
    set_target_properties(gmcl_rtmidi PROPERTIES SUFFIX "_win32.dll")
  else()
    set_target_properties(gmcl_rtmidi PROPERTIES SUFFIX "_win64.dll")
  endif()
endif()
