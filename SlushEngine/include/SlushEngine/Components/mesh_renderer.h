#pragma once
#include <SlushEngine/Components/component.h>
#include <SlushEngine/export.hpp>
#include <SlushEngine/rendering.h>

namespace SlushEngine {
    class SLUSH_EXPORT MeshRenderer : public Component {
        public:
            SlushEngine::Mesh mesh;
            Material material;
            MeshRenderer(Mesh mesh, Material material);
            void Awake() override;
            void Start() override;
            void Update(float dt) override;
            void PhysicsUpdate() override;
    };
}
