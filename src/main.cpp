#include "SlushEngine/application.h"
#include <rlImGui.h>

int main(void) {
    SetTraceLogLevel(LOG_FATAL); 
    SlushEngine::Application application; 
    application.Initialize(2560,1440, 60, "Game Engine");
    return 0;
}
