#include <atomic>
#include <cstdint>
#include "core.h"

int SlushEngine::Core::GetUniqueId(){
    static std::atomic<std::uint32_t> uid {0};
    return ++uid;
}
