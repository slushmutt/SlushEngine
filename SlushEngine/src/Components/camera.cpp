#include <SlushEngine/Components/camera.h>
#include <SlushEngine/Components/transform.h>
#include <SlushEngine/Components/game_object.h>
#include <raylib.h>
#include <raymath.h>
#include <SlushEngine/math.h>

SlushEngine::Camera::Camera(float Fov, SlushEngine::Vector3 Position, SlushEngine::Vector3 Target){
    position = Position;
    target = Target;
    fov = Fov;
    camera = new Camera3D();

    camera->target = target;
    camera->position = position;
    camera->projection = projection;
    camera->fovy = fov;
    camera->up = up;
}
void SlushEngine::Camera::Update(float dt){
}
void SlushEngine::Camera::Start(){
}

void SlushEngine::Camera::Awake(){

}
void SlushEngine::Camera::PhysicsUpdate(){}
