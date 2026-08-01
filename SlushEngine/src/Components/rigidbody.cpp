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
#include "Jolt/Math/Quat.h"
#include "Jolt/Physics/Body/MotionType.h"
#include "Jolt/Physics/EActivation.h"
#include <SlushEngine/Components/component.h>
#include <SlushEngine/Components/transform.h>
#include <raylib.h>
#include <SlushEngine/Components/rigidbody.h>
#include <SlushEngine/Components/game_object.h>
#include <SlushEngine/Components/component.h>
#include <SlushEngine/Utility/raylib_extensions.h>

SlushEngine::Rigidbody::Rigidbody(Transform *transform, const JPH::ConvexShapeSettings* settings, JPH::BodyInterface* interface, JPH::EMotionType motion_type, JPH::ObjectLayer object_layer, JPH::EActivation activate){
    activate = activate;
    object_layer = object_layer;
    motion_type = motion_type;
    shape_result = settings->Create();
    shape = shape_result.Get();
    body_settings = (JPH::BodyCreationSettings){
        shape,
        transform->position,
        JPH::Quat::sIdentity(),
        motion_type,
        object_layer
    };
    body_settings.mRestitution = .6f;
    body_settings.mMotionQuality = JPH::EMotionQuality::Discrete;
    body = interface->CreateBody(body_settings);
    interface->AddBody(body->GetID(), activate);
}
SlushEngine::Rigidbody::~Rigidbody(){}
void SlushEngine::Rigidbody::Update(float dt){}
void SlushEngine::Rigidbody::PhysicsUpdate(){
    Transform *transform = owner->GetComponent<Transform>(); 
    transform->position = ToRayLib(body->GetCenterOfMassPosition());
    transform->rotation = ToRayLib(body->GetRotation());
}
void SlushEngine::Rigidbody::Start(){}
void SlushEngine::Rigidbody::Awake(){}

