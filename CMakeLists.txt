cmake_minimum_required(VERSION 3.24)
project(Slush LANGUAGES CXX)   

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

option(SLUSH_SHARED     "Build SlushEngine as a shared library" ON)
option(SLUSH_BUILD_GAMES "Build the bundled games"              ON)

if(EMSCRIPTEN)
    set(SLUSH_SHARED OFF)
endif()

include(cmake/Dependencies.cmake)   
add_subdirectory(SlushEngine)

if(SLUSH_BUILD_GAMES)
   add_subdirectory(Games/sandbox)
   add_subdirectory(Games/template)
endif()
