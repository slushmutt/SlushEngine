cmake_minimum_required(VERSION 4.1)  
project(SlushEngine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 23)

set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) 
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) 
    endif()
endif()

include(FetchContent)
FetchContent_Declare(
    Jolt
    URL https://github.com/jrouwe/JoltPhysics/archive/refs/tags/v5.6.0.tar.gz
    SOURCE_SUBDIR Build
)
set(USE_ASSERTS OFF CACHE BOOL "" FORCE)
set(TARGET_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(TARGET_HELLO_WORLD OFF CACHE BOOL "" FORCE)
set(TARGET_PERFORMANCE_TEST OFF CACHE BOOL "" FORCE)
set(TARGET_SAMPLES OFF CACHE BOOL "" FORCE)
set(TARGET_VIEWER OFF CACHE BOOL "" FORCE)
set(JPH_USE_VK OFF CACHE BOOL "" FORCE)
set(JPH_USE_DX12 OFF CACHE BOOL "" FORCE)
set(JPH_USE_MTL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(Jolt)


add_executable(${PROJECT_NAME} src/main.cpp
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
    src/SlushEngine/physics.cpp
    src/SlushEngine/behavior.cpp
    src/SlushEngine/auto_register.cpp
    src/Behaviors/TestBehavior.cpp
)
target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} Jolt)

if (DEFINED PLATFORM AND PLATFORM STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html") # Tell Emscripten to build an example.html file.
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
endif()

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
