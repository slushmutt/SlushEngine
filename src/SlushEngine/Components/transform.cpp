#include "transform.h"
#include <raylib.h>
#include <raymath.h>
#include "../Utility/raylib_extensions.h"
void SlushEngine::Transform::Rotate(float x, float y, float z){
    Quaternion new_rot = QuaternionFromEuler(x * DEG2RAD, y * DEG2RAD, z * DEG2RAD);
    rotation = QuaternionMultiply(rotation,new_rot);
}
Vector3 SlushEngine::Transform::EulerAngles(bool deg){
    return deg ? QuaternionToEuler(rotation) * RAD2DEG : QuaternionToEuler(rotation);
}

void SlushEngine::Transform::Awake() {}
void SlushEngine::Transform::Start() {}
void SlushEngine::Transform::Update(float dt) {}
