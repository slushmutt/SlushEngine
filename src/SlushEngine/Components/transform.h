#pragma once
#include "component.h"
#include <raylib.h>
namespace SlushEngine {
    class Transform : public Component {
        public:
            Vector3 position = {0.0f, 0.0f, 0.0f};
            Quaternion rotation = {0.0f, 0.0f, 0.0f, 1.0f};
            Vector3 scale = {0.0f, 0.0f, 0.0f};
            void Rotate(float x, float y, float z);
            Vector3 EulerAngles(bool deg = false);

            void Awake() override;
            void Start() override;
            void Update(float dt) override;
    };
}
