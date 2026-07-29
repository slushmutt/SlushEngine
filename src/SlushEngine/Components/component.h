#pragma once

namespace SlushEngine{
    class GameObject;

    class Component{
        public:
            GameObject* owner;
            virtual ~Component() = default;
            virtual void Awake() {}
            virtual void Start() {}
            virtual void Update(float dt) {}
    };
}

