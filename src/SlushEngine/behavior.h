#pragma once
#include "core.h"

namespace SlushEngine {
    class Behavior{
        public:
            virtual void Update(float dt);
            virtual void PhysicsUpdate();
            virtual void Start();
            virtual void Awake();
    };
}
