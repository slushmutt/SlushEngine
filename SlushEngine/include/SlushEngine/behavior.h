#pragma once
#include <SlushEngine/core.h>
#include <SlushEngine/export.hpp>


namespace SlushEngine {
    class SLUSH_EXPORT Behavior{
        public:
            virtual void Update(float dt);
            virtual void PhysicsUpdate();
            virtual void Start();
            virtual void Awake();
    };
}
