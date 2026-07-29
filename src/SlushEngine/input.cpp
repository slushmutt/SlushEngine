#include <raylib.h>
#include "input.h"
Vector2 SlushEngine::Input::AsVector2Composite(KeyboardKey up, KeyboardKey down, KeyboardKey left, KeyboardKey right){
    return Vector2{
        .x = IsKeyDown(left) ? -1.0f : IsKeyDown(right) ? 1.0f : 0.0f,
        .y = IsKeyDown(down) ? -1.0f : IsKeyDown(up) ? 1.0f : 0.0f
    };
} 

