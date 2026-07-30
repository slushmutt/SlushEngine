#include <atomic>
#include <cstdint>
#include "core.h"

std::vector<SlushEngine::Scene*> SlushEngine::Core::active_scenes;
std::vector<SlushEngine::Behavior*> SlushEngine::Core::active_behaviors;
Camera3D *SlushEngine::Core::main_camera = {0};
JPH::BodyInterface *SlushEngine::Core::body_interface;
int SlushEngine::Core::GetUniqueId(){
    static std::atomic<std::uint32_t> uid {0};
    return ++uid;
}
