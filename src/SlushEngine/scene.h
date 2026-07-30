#include <cstdint>
#include <memory>
#include <vector>
#include "Components/game_object.h"
namespace SlushEngine {
    class Scene{
        public: 
            std::string name;
            template<typename... Args>
            bool AddObject(GameObject obj, Args... args){
                objects.push_back(&obj);
                if constexpr (sizeof...(args) > 0) {
                    return AddObject(std::forward<Args>(args)...);
                }
                return true;
            }
            const std::vector<std::unique_ptr<GameObject>>& GetObjects();
            void Update(float dt);
            void PhysicsUpdate();
            void Start();
            void Awake();
            Scene();
            ~Scene();
        private:
            uint32_t id; 
            std::vector<GameObject*> objects;
    };
}
