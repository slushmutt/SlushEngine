#include "main_behavior.h"
#include <SlushEngine/Components/camera.h>
#include <SlushEngine/Components/transform.h>
#include <SlushEngine/Components/mesh_renderer.h>
#include <SlushEngine/core.h>

using namespace SlushEngine;

Scene scene;
SlushEngine::Camera *camera;
void MainBehavior::Start(){
    GameObject* camera_obj = scene.CreateObject();

    camera = camera_obj->AddComponent<SlushEngine::Camera>(90, Vec3(0,100,0));
    Core::main_camera = camera;

    auto cube = scene.CreateObject(GameObject::CreatePrimitive(Primitive::Cube, SlushEngine::Color(255,255,255,255), Vec3(0,-10,0), Vec3(100,1,100)));

}
