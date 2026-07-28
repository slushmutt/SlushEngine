#include <print>
#include <raylib.h>
#include "application.h"
/**
 *Creates a window and locks the fps.
*/
void SlushEngine::Application::Initialize(int width, int height, int fps, const char *window_title){
    InitWindow(width, height, window_title);
    SetTargetFPS(fps);
    Loop();
}
/**
 *Main application loop, handles the basic drawing and window closing logic.
 */
void SlushEngine::Application::Loop(){
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
}
