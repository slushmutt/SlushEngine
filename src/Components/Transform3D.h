#pragma once
#include "component.h"
#include <raylib.h>

class Transform3D : public Component {
    public:
        Vector3 position = {0.0f, 0.0f, 0.0f};
        Vector3 rotation = {0.0f, 0.0f, 0.0f};
        Vector3 scale = {0.0f, 0.0f, 0.0f};

        void Awake() override;
        void Start() override;
        void Update(float dt) override;
};
