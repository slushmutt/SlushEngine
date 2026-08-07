#include "main_behavior.h"
#include "SlushEngine/math.h"
#include <SlushEngine/Components/game_object.h>
#include <SlushEngine/Components/rigidbody.h>
#include <SlushEngine/debug.h>
#include <SlushEngine/Components/camera.h>
#include <SlushEngine/Components/transform.h>
#include <SlushEngine/Components/mesh_renderer.h>
#include <SlushEngine/core.h>
#include <SlushEngine/rendering.h>
#include <SlushEngine/input.h>

using namespace SlushEngine;

Scene scene;
SlushEngine::Camera *camera;

GameObject* player;
GameObject* camera_obj; 

Rigidbody* player_body;
void MainBehavior::Start(){
    camera_obj = scene.CreateObject();

    camera = camera_obj->AddComponent<SlushEngine::Camera>(90, Vec3(0,25,0));
    Core::main_camera = camera;

    auto floor = scene.CreateObject(GameObject::CreatePrimitive(Primitive::Cube, SlushEngine::Color(255,255,255,255), Vec3(0,-10,0), Vec3(100,1,100)));
    auto wall = scene.CreateObject(GameObject::CreatePrimitive(Primitive::Cube, SlushEngine::Color(255,255,255,255), Vec3(25,-10,0), Vec3(10,50,10)));
    floor->AddComponent<Rigidbody>(Primitive::Cube, MotionType::Static);
    wall->AddComponent<Rigidbody>(Primitive::Cube, MotionType::Static);
    player = scene.CreateObject(GameObject::CreatePrimitive(Primitive::Cube, SlushEngine::Color(255,0,0,255), Vec3(0,0,0), Vec3(1, 2, 1)));
    // SlushEngine::Texture texture = LoadTexture("resources/bald.png"); 
    // floor->GetComponent<MeshRenderer>()->material.maps[::MATERIAL_MAP_DIFFUSE].texture = (SlushEngine::Texture) texture;
    player_body = player->AddComponent<Rigidbody>(Primitive::Cube, MotionType::Dynamic);
    

}

float speed = 10;
float jump_force = 10;
float y = 0;
float z = 0;

void MainBehavior::Update(float delta_time){
    Camera3D *cam = camera->camera;
    Vec2 input = Input::AsVector2Composite(::KEY_W, ::KEY_S, ::KEY_A, ::KEY_D);
    
    // HideCursor();
    y += Input::GetMouseDelta().x * 0.1;
    z += -Input::GetMouseDelta().y * 0.1;
    // SetMousePosition(500, 500);

    camera->position = player_body->GetPosition();
    camera->position.y = player_body->GetPosition().y + 1;

    camera->SetRotation(Vec3(0,z,y));

    Vec3 f = camera_obj->transform->forward;
    Vec3 r = camera_obj->transform->right;
    f.y = 0;
    r.y = 0;

    // f = Vector3Normalize(f);
    // r = Vector3Normalize(r);
    Vec3 move_dir = (f * -input.y) + (r * input.x);          

    if(Input::KeyPressed(::KEY_SPACE)) player_body->SetLinearVelocity(Vec3(
                player_body->body->GetLinearVelocity().GetX(), 
                player_body->body->GetLinearVelocity().GetY() + jump_force, 
                player_body->body->GetLinearVelocity().GetZ()));
    player_body->SetLinearVelocity(Vec3(move_dir.x * speed, player_body->body->GetLinearVelocity().GetY(), move_dir.z * speed));

}

