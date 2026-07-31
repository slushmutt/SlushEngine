#pragma once
#include <SlushEngine/Components/component.h>
#include <SlushEngine/export.hpp>
#include <raylib.h>
#include <vector>

namespace JPH { class BodyInterface; } 
namespace SlushEngine {
    class SLUSH_EXPORT Scene;
    class SLUSH_EXPORT Behavior;
    class SLUSH_EXPORT Core{
        public:
            static std::vector<Scene*> active_scenes;
            static std::vector<Behavior*> active_behaviors;
            static Camera3D *main_camera;
            static JPH::BodyInterface *body_interface;
            static int GetUniqueId();
    };
}
