#include "SlushEngine/application.h"
#include <rlImGui.h>

int main(void) {
    SlushEngine::Application application; 
    application.Initialize(1280, 720, 60, "Game Engine");
    return 0;
}
