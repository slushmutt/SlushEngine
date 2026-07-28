#include <atomic>
#include <cstdint>
#include "slush_core.h"

int SlushCore::GetUniqueId(){
    static std::atomic<std::uint32_t> uid {0};
    return ++uid;
}
