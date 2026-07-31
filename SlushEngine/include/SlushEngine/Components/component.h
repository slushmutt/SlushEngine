#pragma once
#include <SlushEngine/export.hpp>
namespace SlushEngine{
    class SLUSH_EXPORT GameObject;

    class SLUSH_EXPORT Component{
        public:
            GameObject* owner;
            virtual ~Component() = default;
            virtual void Awake() {}
            virtual void Start() {}
            virtual void Update(float dt) {}
            virtual void PhysicsUpdate() {}
    };
}

