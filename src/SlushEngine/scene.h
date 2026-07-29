#include <cstdint>
#include <memory>
#include <vector>
#include "Components/game_object.h"
namespace SlushEngine {
    class Scene{
        public: 
            std::string name;
            bool AddObject(std::unique_ptr<SlushEngine::GameObject> obj);
            const std::vector<std::unique_ptr<GameObject>>& GetObjects();
            void Update(float dt);
            void Start();
            void Awake();
            Scene();
            ~Scene();
        private:
            uint32_t id; 
            std::vector<std::unique_ptr<GameObject>> objects;
    };
}
