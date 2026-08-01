#include <SlushEngine/Components/transform.h>
#include <SlushEngine/math.h>
#include <raylib.h>
#include <raymath.h>
#include <SlushEngine/Utility/raylib_extensions.h>
SlushEngine::Transform::Transform(SlushEngine::Vector3 Position, SlushEngine::Vector3 Scale, ::Quaternion Rotation){
    position = Position;
    rotation = Rotation;
    scale = Scale;
}
void SlushEngine::Transform::Rotate(float x, float y, float z){
    ::Quaternion new_rot = QuaternionFromEuler(x * DEG2RAD, y * DEG2RAD, z * DEG2RAD);
    rotation = QuaternionNormalize(QuaternionMultiply(new_rot, rotation));
}
SlushEngine::Vector3 SlushEngine::Transform::EulerAngles(bool deg){
    return deg ? QuaternionToEuler(rotation) * RAD2DEG : QuaternionToEuler(rotation);
}

void SlushEngine::Transform::Awake() {}
void SlushEngine::Transform::Start() {}
void SlushEngine::Transform::Update(float dt) {}
void SlushEngine::Transform::PhysicsUpdate() {}
