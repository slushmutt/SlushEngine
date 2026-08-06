#pragma once
#include <SlushEngine/math.h>
#include <cstdint>
#include <memory>
#include <vector>
#include <SlushEngine/export.hpp>
namespace SlushEngine {
    class GameObject;

    class SLUSH_EXPORT Scene{
        public: 
            std::string name;

            GameObject* CreateObject(Vector3 position = Vector3(), Vector3 scale = Vector3(1,1,1), Quaternion rotation = Quaternion(0,0,0,1));
            GameObject* CreateObject(GameObject& obj);
            template<typename... Args>
            bool AddObject(std::unique_ptr<GameObject> obj, Args... args);
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

