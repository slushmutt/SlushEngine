#include <atomic>
#include <cstdint>
#include "core.h"

std::vector<SlushEngine::Scene*> SlushEngine::Core::active_scenes;
int SlushEngine::Core::GetUniqueId(){
    static std::atomic<std::uint32_t> uid {0};
    return ++uid;
}
