#include <SlushEngine/input.h>
#include <SlushEngine/math.h>
#include <raylib.h>

SlushEngine::Vector2 SlushEngine::Input::AsVector2Composite(int up, int down, int left, int right){
    return SlushEngine::Vector2(
        IsKeyDown(left) ? -1.0f : IsKeyDown(right) ? 1.0f : 0.0f,
        IsKeyDown(down) ? -1.0f : IsKeyDown(up) ? 1.0f : 0.0f
    );
} 
int SlushEngine::Input::KeyDown(int key){
    return IsKeyDown(key);
}

int SlushEngine::Input::KeyPressed(int key){
    return IsKeyPressed(key);
}

int SlushEngine::Input::KeyUp(int key){
    return IsKeyUp(key);
}
SlushEngine::Vector2 SlushEngine::Input::GetMousePosition(){ 
    return GetMousePosition();
}

