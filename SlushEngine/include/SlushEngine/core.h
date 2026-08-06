#pragma once
#include <SlushEngine/export.hpp>
#include <SlushEngine/scene.h>
#include <SlushEngine/math.h>
#include <SlushEngine/Components/game_object.h>
#include <SlushEngine/Components/component.h>
#include <vector>

namespace JPH { class BodyInterface; } 
namespace SlushEngine {
    class  Behavior;
    class  Camera;
    class SLUSH_EXPORT Core{
        public:
            static std::vector<Scene*> active_scenes;
            static std::vector<Behavior*> active_behaviors;
            static  SlushEngine::Camera *main_camera;
            static JPH::BodyInterface *body_interface;
            static int GetUniqueId();
    };
}
