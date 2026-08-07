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
#include "Jolt/Physics/Body/MotionQuality.h"
#include "Jolt/Physics/Body/MotionType.h"
#include "Jolt/Physics/Collision/Shape/ConvexShape.h"
#include "Jolt/Physics/Collision/Shape/CylinderShape.h"
#include "Jolt/Physics/EActivation.h"
#include <SlushEngine/debug.h>
#include <SlushEngine/core.h>
#include <SlushEngine/math.h>
#include <SlushEngine/Components/component.h>
#include <SlushEngine/Components/transform.h>
#include <memory>
#include <raylib.h>
#include <SlushEngine/Components/rigidbody.h>
#include <SlushEngine/Components/game_object.h>
#include <SlushEngine/Components/component.h>

std::unique_ptr<JPH::ConvexShapeSettings> SlushEngine::Rigidbody::GetSettings(SlushEngine::Primitive primitive) {
    auto a = owner->transform->scale;
    std::unique_ptr<JPH::ConvexShapeSettings> r = nullptr;

    SlushEngine::Vector3 half_extents = SlushEngine::Vector3(0.5f * a.x, 0.5f * a.y, 0.5f * a.z);



    switch (primitive) {
        case SlushEngine::Cube: 
            r = std::make_unique<JPH::BoxShapeSettings>(half_extents); 
            break;

        case SlushEngine::Sphere: 
            r = std::make_unique<JPH::SphereShapeSettings>(owner->transform->scale.x); 
            break;

        case SlushEngine::Cylinder: 
            r = std::make_unique<JPH::CylinderShapeSettings>(half_extents.y, half_extents.x); 
            break;

        case SlushEngine::Plane: 
            half_extents.y = 0.01f; 
            r = std::make_unique<JPH::BoxShapeSettings>(half_extents);
            break;
        default:
            r = nullptr;
    }
    return r;
}
SlushEngine::Primitive p;
SlushEngine::Rigidbody::Rigidbody(SlushEngine::Primitive Primitive, MotionType Motion_type, JPH::ObjectLayer Object_layer, JPH::EActivation Activate) {
    activate = Activate;
    object_layer = Object_layer;
    motion_type = Motion_type;
    
    p = Primitive;
}

void SlushEngine::Rigidbody::SetPosition(Vector3 pos){
    SlushEngine::Core::body_interface->SetPosition(this->body->GetID(), pos, this->activate);
}

void SlushEngine::Rigidbody::SetLinearVelocity(Vector3 vel){
    SlushEngine::Core::body_interface->SetLinearVelocity(this->body->GetID(), vel);
}

SlushEngine::Vector3 SlushEngine::Rigidbody::GetPosition(){
    return (Vector3) body->GetPosition();
}


void SlushEngine::Rigidbody::Start() {
}
SlushEngine::Rigidbody::~Rigidbody(){}
void SlushEngine::Rigidbody::Update(float dt){}
void SlushEngine::Rigidbody::PhysicsUpdate(){
    owner->transform->position = body->GetCenterOfMassPosition();
    owner->transform->rotation = body->GetRotation();
}
void SlushEngine::Rigidbody::Awake(){
    auto settings = GetSettings(p); 

    if (!settings) return;

    shape_result = settings->Create();
    shape = shape_result.Get();

    JPH::Vec3 jphPos(owner->transform->position.x, owner->transform->position.y, owner->transform->position.z);

    body_settings = JPH::BodyCreationSettings(
        shape,
        jphPos,
        JPH::Quat::sIdentity(),
        (JPH::EMotionType) motion_type,
        object_layer
    );

    body_settings.mRestitution = 0.1f;
    body_settings.mMotionQuality = JPH::EMotionQuality::Discrete;

    body = SlushEngine::Core::body_interface->CreateBody(body_settings);
    SlushEngine::Core::body_interface->AddBody(body->GetID(), activate);
}


