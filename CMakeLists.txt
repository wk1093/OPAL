cmake_minimum_required(VERSION 3.26)
project(opal)

option(BUILD_OPAL "Build OPAL Library" ON)
option(BUILD_EXAMPLES "Build Examples" ON)

# Implementations
option(OPAL_PORTAUDIO "Use PortAudio" ON)

# versioning
set(OPAL_VERSION_MAJOR 0)
set(OPAL_VERSION_MINOR 2)
set(OPAL_VERSION_PATCH 0)

set(PROJECT_VERSION ${OPAL_VERSION_MAJOR}.${OPAL_VERSION_MINOR}.${OPAL_VERSION_PATCH})
# this version goes into the header eogll_version.h
configure_file(
        "include/opal/version.h.in"
        "${PROJECT_BINARY_DIR}/include/opal/version.h"
)

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()


set(CMAKE_C_STANDARD 11)

# allow disabling of all libraries for docs

if (BUILD_OPAL)
    include(FetchContent)

    FetchContent_Declare(
            hedley
            GIT_REPOSITORY https://github.com/nemequ/hedley.git
            GIT_TAG v15
    )
    FetchContent_MakeAvailable(hedley)
    add_library(hedley INTERFACE IMPORTED)
    target_include_directories(hedley INTERFACE ${hedley_SOURCE_DIR})



    add_library(opal STATIC include/opal.h
            include/opal/pch.h
            include/opal/stream.h
            include/opal/synth.h
            include/opal/sound.h
            src/version.c
            src/stream.c
            src/opal.c
            src/synth.c
            src/sound.c)
    target_include_directories(opal PUBLIC include ${PROJECT_BINARY_DIR}/include)

    target_link_libraries(opal PUBLIC hedley)
    
    if (OPAL_PORTAUDIO)
        FetchContent_Declare(
                portaudio
                GIT_REPOSITORY https://github.com/PortAudio/portaudio.git
                GIT_TAG v19.7.0
        )
        FetchContent_MakeAvailable(portaudio)
        target_compile_definitions(opal PUBLIC OPAL_PORTAUDIO)
        target_link_libraries(opal PUBLIC portaudio_static)
    endif()


    if (CMAKE_BUILD_TYPE MATCHES Debug)
        message("Debug build.")
        target_compile_definitions(opal PUBLIC OPAL_DEBUG)
    endif()

    if (BUILD_EXAMPLES)
        add_subdirectory(examples)
    endif()
endif()
