#include <raylib.h>
#include "application.h"
/**
 *Creates a window and locks the fps.
*/
void initialize_window(int width, int height, int fps, const char *window_title){
    InitWindow(width, height, window_title);
    SetTargetFPS(fps);
    application_loop();
}
/**
 *Main application loop, handles the basic drawing and window closing logic.
 */
void application_loop(){
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
}
