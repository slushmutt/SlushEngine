#pragma once
#include <vector>

namespace SlushEngine {
    class Scene;
    class Core{
        public:
            static std::vector<Scene*> active_scenes;
            static int GetUniqueId();
    };
}
