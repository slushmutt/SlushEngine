#pragma once
#include <SlushEngine/Components/game_object.h>
#include <SlushEngine/physics.h>
#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <SlushEngine/export.hpp>
#include <SlushEngine/Components/component.h>
#include <memory>

namespace SlushEngine {
    enum Primitive;
    class SLUSH_EXPORT Rigidbody : public Component {
        public:
            JPH::ShapeSettings::ShapeResult shape_result;
            JPH::ShapeRefC shape;
            JPH::BodyCreationSettings body_settings;
            JPH::Body* body;
            JPH::EMotionType motion_type;
            JPH::ObjectLayer object_layer;
            JPH::EActivation activate;
            class Transform;
            Rigidbody(const Primitive primitive, JPH::EMotionType motion_type, JPH::ObjectLayer object_layer = Layers::MOVING, JPH::EActivation = JPH::EActivation::Activate);
            ~Rigidbody();
            void Awake() override;
            void Start() override;
            void Update(float dt) override;
            void PhysicsUpdate() override;
        private:
            Primitive primitive;
            std::unique_ptr<JPH::ConvexShapeSettings> GetSettings(Primitive primitive);
    };
}
