#pragma once
#include <SlushEngine/Components/component.h>
#include <raylib.h>
#include <SlushEngine/export.hpp>
namespace SlushEngine {
    class SLUSH_EXPORT MeshRenderer : public Component {
        public:
            Mesh mesh;
            Material material;
            MeshRenderer(Mesh mesh, Material material);
            void Awake() override;
            void Start() override;
            void Update(float dt) override;
            void PhysicsUpdate() override;
    };
}
