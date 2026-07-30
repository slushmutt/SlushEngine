#pragma once
namespace SlushEngine {
    /**
     *Base application class, handles the window and OpenGL context.
     */
    class Application {
        public: 
            /**
            *Creates a window and locks the fps.
            *Also initializes the JoltPhysics engine and rlImGui.
            *Then runs the awake function on all behaviors and objects.
            */
            void Initialize(int width, int height, int fps, const char *window_title);
            /**
             *Main application loop, handles the basic drawing and window closing logic.
             *Also handles the JoltPhysics contexts and the rlImGui Rendering.
            */
            void Loop();
            Application() = default;
            ~Application() = default;
    };
}

