add_executable(Template
    src/main.cpp
    src/Behaviors/main_behavior.cpp
)

target_include_directories(Template PRIVATE src)
target_link_libraries(Template PRIVATE Slush::Engine)

set_target_properties(Template PROPERTIES
    BUILD_RPATH   "$ORIGIN"
    INSTALL_RPATH "$ORIGIN"
)

if(WIN32)
    add_custom_command(TARGET Template POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_RUNTIME_DLLS:Template> $<TARGET_FILE_DIR:Template>
        COMMAND_EXPAND_LISTS)
endif()

if(EMSCRIPTEN)
    set_target_properties(Template PROPERTIES SUFFIX ".html")
    target_link_options(Template PRIVATE
        -sUSE_GLFW=3 -sASSERTIONS=1 -sWASM=1 -sASYNCIFY
        -sGL_ENABLE_GET_PROC_ADDRESS=1)
endif()
