if(SLUSH_SHARED)
    add_library(SlushEngine SHARED)
else()
    add_library(SlushEngine STATIC)
endif()
add_library(Slush::Engine ALIAS SlushEngine)

target_sources(SlushEngine PRIVATE
    src/application.cpp
    src/scene.cpp
    src/core.cpp
    src/input.cpp
    src/rendering.cpp
    src/physics.cpp
    src/behavior.cpp
    src/auto_register.cpp
    src/debug.cpp
    src/debug_colors.cpp
    src/Components/game_object.cpp
    src/Components/component.cpp
    src/Components/transform.cpp
    src/Components/mesh_renderer.cpp
    src/Components/camera.cpp
    src/Components/rigidbody.cpp
    src/Utility/raylib_extensions.cpp
    src/Utility/type_extension.cpp
)

target_include_directories(SlushEngine
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(SlushEngine
    PUBLIC  raylib
    PUBLIC Jolt imgui rlimgui
)

set_target_properties(SlushEngine PROPERTIES
    CXX_VISIBILITY_PRESET     hidden
    VISIBILITY_INLINES_HIDDEN ON
    VERSION  0.1.0
    SOVERSION 0
)

include(GenerateExportHeader)
generate_export_header(SlushEngine
    BASE_NAME        SLUSH
    EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/include/SlushEngine/export.hpp
)

if(NOT SLUSH_SHARED)
    target_compile_definitions(SlushEngine PUBLIC SLUSH_STATIC_DEFINE)
endif()

if(MSVC)
    target_compile_options(SlushEngine PRIVATE /permissive- /W4)
    target_compile_options(SlushEngine PUBLIC /wd4251)
endif()

if(APPLE)
    target_link_libraries(SlushEngine PRIVATE
        "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif()
