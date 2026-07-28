#include <raylib.h>
#include "SlushEngine/application.h"

using namespace SlushEngine;

int main(void) {
    Application application; 
    application.Initialize(1280, 720, 60, "Game Engine");
    return 0;
}
