#pragma once
#include "Components/camera.h"
#include <Jolt/Jolt.h>
#include "Jolt/Physics/Body/BodyInterface.h"
#include <raylib.h>
#include <vector>

namespace SlushEngine {
    class Scene;
    class Behavior;
    class Core{
        public:
            static std::vector<Scene*> active_scenes;
            static std::vector<Behavior*> active_behaviors;
            static Camera3D *main_camera;
            static JPH::BodyInterface *body_interface;
            static int GetUniqueId();
    };
}
