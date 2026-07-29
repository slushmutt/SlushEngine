#pragma once
#include "component.h"
#include <raylib.h>
namespace SlushEngine {
    class MeshRenderer : public Component {
        public:
            Mesh mesh;
            Material material;
            void Awake() override;
            void Start() override;
            void Update(float dt) override;
    };
}
