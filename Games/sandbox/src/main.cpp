#include <SlushEngine/application.h>

int main() {
    SlushEngine::Application app;
    app.Initialize(1280, 720, 60, "Sandbox");
    app.Loop();
    return 0;
}
