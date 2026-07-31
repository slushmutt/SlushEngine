#include <cstdint>
#include <memory>
#include <vector>
#include <SlushEngine/Components/game_object.h>
#include <SlushEngine/export.hpp>
namespace SlushEngine {
    class SLUSH_EXPORT Scene{
        public: 
            std::string name;
            template<typename... Args>
            bool AddObject(std::unique_ptr<GameObject> obj, Args... args){
                objects.push_back(std::move(obj));
                if constexpr (sizeof...(args) > 0) {
                    return AddObject(std::forward<Args>(args)...);
                }
                return true;
            }
            std::vector<std::unique_ptr<GameObject>>& GetObjects();
            void Update(float dt);
            void PhysicsUpdate();
            void Start();
            void Awake();
            Scene();
            ~Scene();
        private:
            uint32_t id; 
            std::vector<std::unique_ptr<GameObject>> objects;
    };
}
