#pragma once
#include "component.h"
#include <raylib.h>
namespace SlushEngine {
    class Camera : public Component {
        public: 
            Camera3D camera = {0};
            Vector3 target = (Vector3){ 0.0f, 0.0f, 0.0f };
            Vector3 up = (Vector3){ 0.0f, 1.0f, 0.0f };
            float fov = 45.0f;
            int projection = CAMERA_PERSPECTIVE;
            Camera(Vector3 target, float fov);
            void Awake() override;
            void Start() override;
            void Update(float dt) override;
            void PhysicsUpdate() override;
    };
}
