cmake_minimum_required(VERSION 3.14)
project(ffaudio)

include(./third_party/vendor_tools/vendor.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


if (MSVC)
    string(TOLOWER ${MSVC_C_ARCHITECTURE_ID} ARCH)
elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" OR $CMAKE_SYSTEM_PROCESSOR STREQUAL "amd64")
    set(ARCH x64)
elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
    set(ARCH arm64)
else ()
    set(ARCH x86)
endif ()
if (APPLE)
    set(PLATFORM mac)
elseif (WIN32)
    set(PLATFORM win)
endif ()

# Sets the default build type to release.
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif ()

if (MSVC)
    add_compile_options("/utf-8")
endif (MSVC)

# collects include directories.
set(FFAUDIO_INCLUDES include src/AudioMuxerImpl vendor/ffmpeg/include)

# collects source files.
set(FFAUDIO_FILES src/ffaudio.cpp src/AudioMuxerImpl/AudioMuxerImpl.cpp)

add_compile_options(-fvisibility=hidden)

file(GLOB FFMPEG_FILES vendor/ffmpeg/${PLATFORM}/${ARCH}/*${CMAKE_STATIC_LIBRARY_SUFFIX})
list(APPEND FFAUDIO_STATIC_LIBS ${FFMPEG_FILES})

if (APPLE)
    add_compile_options(-stdlib=libc++)
elseif (WIN32)
    find_library(Bcrypt_LIB Bcrypt)
    find_library(WS2_LIB ws2_32)
    list(APPEND FFAUDIO_STATIC_LIBS ${Bcrypt_LIB} ${WS2_LIB})
    if (MSVC)
        add_compile_options("/MD")
    endif ()
endif ()

if (FFAUDIO_BUILD_STATIC)
    add_library(ffaudio STATIC ${FFAUDIO_FILES})
    merge_libraries_into(ffaudio ${FFAUDIO_STATIC_LIBS})
else ()
    add_library(ffaudio SHARED ${FFAUDIO_FILES})
endif ()

target_include_directories(ffaudio PRIVATE ${FFAUDIO_INCLUDES})
target_link_libraries(ffaudio PRIVATE ${FFAUDIO_STATIC_LIBS})