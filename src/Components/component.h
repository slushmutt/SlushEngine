#pragma once
class Component{
    public:
        virtual ~Component() = default;
        virtual void Awake() {}
        virtual void Start() {}
        virtual void Update(float dt) {}
};
