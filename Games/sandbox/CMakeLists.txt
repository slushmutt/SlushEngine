add_executable(Sandbox
    src/main.cpp
    src/Behaviors/TestBehavior.cpp
)

target_include_directories(Sandbox PRIVATE src)
target_link_libraries(Sandbox PRIVATE Slush::Engine)

set_target_properties(Sandbox PROPERTIES
    BUILD_RPATH   "$ORIGIN"
    INSTALL_RPATH "$ORIGIN"
)

if(WIN32)
    add_custom_command(TARGET Sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_RUNTIME_DLLS:Sandbox> $<TARGET_FILE_DIR:Sandbox>
        COMMAND_EXPAND_LISTS)
endif()

if(EMSCRIPTEN)
    set_target_properties(Sandbox PROPERTIES SUFFIX ".html")
    target_link_options(Sandbox PRIVATE
        -sUSE_GLFW=3 -sASSERTIONS=1 -sWASM=1 -sASYNCIFY
        -sGL_ENABLE_GET_PROC_ADDRESS=1)
endif()
