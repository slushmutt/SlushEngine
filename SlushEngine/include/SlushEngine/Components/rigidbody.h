#pragma once
#include <SlushEngine/math.h>
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

    enum class MotionType : uint8_t
    {
        Static,						
        Kinematic,					
        Dynamic,					
    };

    class SLUSH_EXPORT Rigidbody : public Component {
        public:
            JPH::ShapeSettings::ShapeResult shape_result;
            JPH::ShapeRefC shape;
            JPH::BodyCreationSettings body_settings;
            JPH::Body* body;
            MotionType motion_type;
            JPH::ObjectLayer object_layer;
            JPH::EActivation activate;
            class Transform;
            Rigidbody(const Primitive primitive, MotionType motion_type, JPH::ObjectLayer object_layer = Layers::MOVING, JPH::EActivation = JPH::EActivation::Activate);
            ~Rigidbody();
            Vector3 GetPosition();
            void SetPosition(Vector3 pos);
            void SetLinearVelocity(Vector3 vel);
            void Awake() override;
            void Start() override;
            void Update(float dt) override;
            void PhysicsUpdate() override;
        private:
            Primitive primitive;
            std::unique_ptr<JPH::ConvexShapeSettings> GetSettings(Primitive primitive);
    };
}
