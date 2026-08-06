#pragma once
#include <SlushEngine/export.hpp>
namespace SlushEngine {
    /**
    * @brief Base application class, handles the window and OpenGL context.
    * @ingroup application
    *
    * The application owns the window, the OpenGL context, and the
    * frame loop. Create an Application, call Initialize() with the
    * resolution and framerate, then whatever behaviors are autoloaded will take over. \n
    * Below is a basic example on how to create an application.
    * #### Note: You must have atleast one @ref behavior registered along with atleast one @ref scene for this to not immediately close.
    *
    * Example application setup:
    * @code{.cpp}
    * #include <SlushEngine/application.h>
    *
    * int main() {
    *   SlushEngine::Application app;
    *   app.Initialize(1280, 720, 60, "Game");
    *   return 0;
    * }
    * @endcode
    */
    class SLUSH_EXPORT Application {
        public: 
            /**
            * @brief Creates a window with the width and height provided, locks fps to fps value provided.
            *
            * For the application to not immediately close, you must have atleast one @ref behavior, and one @ref scene
            *
            * @param width The windows width in pixels (e.g. 1920).
            * @param height The windows height in pixels (e.g. 1080).
            * @param fps The windows max frames per second (e.g. 60).
            * @param window_title The windows title (e.g. "Game").
            *
            */
            void Initialize(int width, int height, int fps, const char *window_title);
            /// @cond
            Application() = default;
            ~Application() = default;
            /// @endcond
        private:
            void Loop();
    };
}

