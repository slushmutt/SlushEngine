#include "main_behavior.h"
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <raylib.h>
#include <SlushEngine/Components/camera.h>
#include <SlushEngine/Components/transform.h>
#include <SlushEngine/scene.h>

SlushEngine::Scene scene;
auto camera_obj = std::make_unique<SlushEngine::GameObject>();
SlushEngine::Camera *camera_cam;
Camera3D camera;

void MainBehavior::Start(){
    camera_cam = camera_obj->AddComponent<SlushEngine::Camera>((Vector3){5,0,5}, 90);
    camera_obj->AddComponent<SlushEngine::Transform>();
    camera = camera_cam->camera;
    SlushEngine::Core::main_camera = &camera;

    scene.AddObject(std::move(camera_obj));
}

void MainBehavior::Update(float dt){
    UpdateCamera(SlushEngine::Core::main_camera, CAMERA_FREE);
}
