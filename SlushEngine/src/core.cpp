#include "SlushEngine/Components/camera.h"
#include <atomic>
#include <cstdint>
#include <SlushEngine/core.h>

std::vector<SlushEngine::Scene*> SlushEngine::Core::active_scenes;
std::vector<SlushEngine::Behavior*> SlushEngine::Core::active_behaviors;

SlushEngine::Camera *SlushEngine::Core::main_camera = {0};

JPH::BodyInterface *SlushEngine::Core::body_interface;

int SlushEngine::Core::GetUniqueId(){
    static std::atomic<std::uint32_t> uid {0};
    return ++uid;
}
