#pragma once
namespace SlushEngine {
    /**
     *Base application class, handles the window and OpenGL context.
     */
    class Application {
        public: 
            /**
            *Creates a window and locks the fps.
            */
            void Initialize(int width, int height, int fps, const char *window_title);
            /**
             *Main application loop, handles the basic drawing and window closing logic.
            */
            void Loop();
            Application() = default;
            ~Application() = default;
    };
}

