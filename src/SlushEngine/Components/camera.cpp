#include "camera.h"
#include "transform.h"
#include "game_object.h"
#include <print>
#include <raylib.h>
#include <raymath.h>
#include "../Utility/raylib_extensions.h"

SlushEngine::Camera::Camera(Vector3 Target, float Fov){
    target = Target;
    fov = Fov;
    camera.target = target;
    camera.projection = projection;
    camera.fovy = fov;
    camera.up = up;
}
void SlushEngine::Camera::Update(float dt){}
void SlushEngine::Camera::Start(){
}

void SlushEngine::Camera::Awake(){

}
void SlushEngine::Camera::PhysicsUpdate(){}
