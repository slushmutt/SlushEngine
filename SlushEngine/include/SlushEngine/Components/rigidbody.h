#pragma once
#include <Jolt/Jolt.h>
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
#include "Jolt/Physics/Body/MotionType.h"
#include "Jolt/Physics/Collision/Shape/ConvexShape.h"
#include "Jolt/Physics/EActivation.h"
#include <SlushEngine/Components/component.h>
#include <raylib.h>
#include <SlushEngine/physics.h>
#include <SlushEngine/Components/transform.h>
#include <SlushEngine/export.hpp>
namespace SlushEngine {
    class SLUSH_EXPORT Rigidbody : public Component {
        public:
            JPH::ShapeSettings::ShapeResult shape_result;
            JPH::ShapeRefC shape;
            JPH::BodyCreationSettings body_settings;
            JPH::Body *body;
            JPH::EMotionType motion_type;
            JPH::ObjectLayer object_layer;
            JPH::EActivation activate;
            Rigidbody(Transform *transform, const JPH::ConvexShapeSettings* settings, JPH::BodyInterface* interface, JPH::EMotionType motion_type, JPH::ObjectLayer object_layer, JPH::EActivation activate);
            ~Rigidbody();
            void Awake() override;
            void Start() override;
            void Update(float dt) override;
            void PhysicsUpdate() override;
    };
}
