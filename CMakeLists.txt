cmake_minimum_required(VERSION 4.1)
project(SlushEngine CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
    FetchContent_Declare(
        raylib
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_MakeAvailable(raylib)
endif()

set(USE_ASSERTS            OFF CACHE BOOL "" FORCE)
set(TARGET_UNIT_TESTS      OFF CACHE BOOL "" FORCE)
set(TARGET_HELLO_WORLD     OFF CACHE BOOL "" FORCE)
set(TARGET_PERFORMANCE_TEST OFF CACHE BOOL "" FORCE)
set(TARGET_SAMPLES         OFF CACHE BOOL "" FORCE)
set(TARGET_VIEWER          OFF CACHE BOOL "" FORCE)
set(JPH_USE_VK             OFF CACHE BOOL "" FORCE)
set(JPH_USE_DX12           OFF CACHE BOOL "" FORCE)
set(JPH_USE_MTL            OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    Jolt
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/jrouwe/JoltPhysics/archive/refs/tags/v5.6.0.tar.gz
    SOURCE_SUBDIR Build
)
FetchContent_MakeAvailable(Jolt)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        docking
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(imgui)

if(NOT TARGET imgui)
    add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    )
    target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})
endif()

FetchContent_Declare(
    rlimgui
    GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
    GIT_TAG        main
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(rlimgui)

if(NOT TARGET rlimgui)
    add_library(rlimgui STATIC
        ${rlimgui_SOURCE_DIR}/rlImGui.cpp
    )
    target_include_directories(rlimgui PUBLIC ${rlimgui_SOURCE_DIR})
    target_link_libraries(rlimgui PUBLIC raylib imgui)
endif()

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/SlushEngine/application.cpp
    src/SlushEngine/scene.cpp
    src/SlushEngine/core.cpp
    src/SlushEngine/input.cpp
    src/SlushEngine/rendering.cpp
    src/SlushEngine/Components/game_object.cpp
    src/SlushEngine/Components/component.cpp
    src/SlushEngine/Components/transform.cpp
    src/SlushEngine/Components/mesh_renderer.cpp
    src/SlushEngine/Components/camera.cpp
    src/SlushEngine/Components/rigidbody.cpp
    src/SlushEngine/Utility/raylib_extensions.cpp
    src/SlushEngine/Utility/type_extension.cpp
    src/SlushEngine/physics.cpp
    src/SlushEngine/behavior.cpp
    src/SlushEngine/auto_register.cpp
    src/SlushEngine/debug.cpp
    src/SlushEngine/debug_colors.cpp
    src/Behaviors/TestBehavior.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PRIVATE
    rlimgui
    raylib
    imgui
    Jolt
)

if (DEFINED PLATFORM AND PLATFORM STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    target_link_options(${PROJECT_NAME} PRIVATE
        -sUSE_GLFW=3
        -sASSERTIONS=1
        -sWASM=1
        -sASYNCIFY
        -sGL_ENABLE_GET_PROC_ADDRESS=1
    )
endif()

if (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL"
    )
endif()
