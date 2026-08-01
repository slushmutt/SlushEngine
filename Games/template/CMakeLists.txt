add_executable(NewGame
    src/main.cpp
    src/Behaviors/main_behavior.cpp
)

target_include_directories(NewGame PRIVATE src)
target_link_libraries(NewGame PRIVATE Slush::Engine)

set_target_properties(NewGame PROPERTIES
    BUILD_RPATH   "$ORIGIN"
    INSTALL_RPATH "$ORIGIN"
)

if(WIN32)
    add_custom_command(TARGET NewGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_RUNTIME_DLLS:NewGame> $<TARGET_FILE_DIR:NewGame>
        COMMAND_EXPAND_LISTS)
endif()

if(EMSCRIPTEN)
    set_target_properties(NewGame PROPERTIES SUFFIX ".html")
    target_link_options(NewGame PRIVATE
        -sUSE_GLFW=3 -sASSERTIONS=1 -sWASM=1 -sASYNCIFY
        -sGL_ENABLE_GET_PROC_ADDRESS=1)
endif()
