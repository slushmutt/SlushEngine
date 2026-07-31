include(FetchContent)

# Some dependency CMakeLists still declare an ancient minimum; CMake 4 refuses
# them outright. This makes them tolerable. Drop it if you never see the error.
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

# ---------------------------------------------------------------- raylib
# Built SHARED deliberately. raylib keeps global state (the window handle,
# the rlgl draw batch). If both your .so and the game .exe statically linked
# it, you'd get two copies of that state and drawing would silently do nothing.
set(BUILD_EXAMPLES  OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES     OFF CACHE BOOL "" FORCE)
set(CUSTOMIZE_BUILD OFF CACHE BOOL "" FORCE)

set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if(NOT raylib_FOUND)
    # Normal variable shadows the cache for this scope only (CMP0077),
    # so raylib goes shared without dragging Jolt/imgui along.
    set(BUILD_SHARED_LIBS ON)
    FetchContent_Declare(raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP OFF)
    FetchContent_MakeAvailable(raylib)
    unset(BUILD_SHARED_LIBS)
endif()

# ---------------------------------------------------------------- Jolt
# Static, and kept PRIVATE to the engine.
set(TARGET_UNIT_TESTS       OFF CACHE BOOL "" FORCE)
set(TARGET_HELLO_WORLD      OFF CACHE BOOL "" FORCE)
set(TARGET_PERFORMANCE_TEST OFF CACHE BOOL "" FORCE)
set(TARGET_SAMPLES          OFF CACHE BOOL "" FORCE)
set(TARGET_VIEWER           OFF CACHE BOOL "" FORCE)
set(USE_ASSERTS             OFF CACHE BOOL "" FORCE)
set(JPH_USE_VK              OFF CACHE BOOL "" FORCE)
set(JPH_USE_DX12            OFF CACHE BOOL "" FORCE)
set(JPH_USE_MTL             OFF CACHE BOOL "" FORCE)
set(DOUBLE_PRECISION        OFF CACHE BOOL "" FORCE)

# These four matter a lot and weren't in your file:
set(OVERRIDE_CXX_FLAGS      OFF CACHE BOOL "" FORCE)  # Jolt otherwise REPLACES
                                                      # CMAKE_CXX_FLAGS_* project-wide
set(CPP_RTTI_ENABLED        ON  CACHE BOOL "" FORCE)  # you need dynamic_cast for
                                                      # a component system
set(CPP_EXCEPTIONS_ENABLED  ON  CACHE BOOL "" FORCE)
set(ENABLE_ALL_WARNINGS     OFF CACHE BOOL "" FORCE)
set(INTERPROCEDURAL_OPTIMIZATION OFF CACHE BOOL "" FORCE)

FetchContent_Declare(Jolt
    URL https://github.com/jrouwe/JoltPhysics/archive/refs/tags/v5.6.0.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    SOURCE_SUBDIR Build)
FetchContent_MakeAvailable(Jolt)

# ---------------------------------------------------------------- Dear ImGui
FetchContent_Declare(imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        docking
    GIT_SHALLOW    TRUE)
FetchContent_MakeAvailable(imgui)

if(NOT TARGET imgui)
    add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp)
    target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})
endif()

# ---------------------------------------------------------------- rlImGui
FetchContent_Declare(rlimgui
    GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
    GIT_TAG        main
    GIT_SHALLOW    TRUE)
FetchContent_MakeAvailable(rlimgui)

# Guard against BOTH spellings — if upstream ever ships its own CMakeLists
# the target may be `rlImGui`, and your lowercase check would define a duplicate.
if(NOT TARGET rlimgui AND NOT TARGET rlImGui)
    add_library(rlimgui STATIC ${rlimgui_SOURCE_DIR}/rlImGui.cpp)
    target_include_directories(rlimgui PUBLIC ${rlimgui_SOURCE_DIR})
    target_link_libraries(rlimgui PUBLIC raylib imgui)
endif()
