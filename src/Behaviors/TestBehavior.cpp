#include "TestBehavior.h"
#include "../SlushEngine/Components/game_object.h"
#include "../SlushEngine/Components/transform.h"
#include "../SlushEngine/Components/mesh_renderer.h"
#include "../SlushEngine/Components/camera.h"
#include "../SlushEngine/Components/rigidbody.h"
#include "../SlushEngine/scene.h"
#include "../SlushEngine/input.h"
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <cstdlib>
#include <format>
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <utility>
#include "../SlushEngine/Utility/raylib_extensions.h"
#include "Jolt/Physics/Body/MotionType.h"
#include "Jolt/Physics/EActivation.h"

SlushEngine::Scene scene;
auto camera_obj = std::make_unique<SlushEngine::GameObject>();
SlushEngine::Camera *camera_cam;
auto sphere_obj = std::make_unique<SlushEngine::GameObject>();
SlushEngine::Transform *sphere_transform;
SlushEngine::Rigidbody *sphere_rigidbody;
Camera3D camera;

void SpawnBox(Vector3 position, Vector3 scale, Color color){
auto floor_obj = std::make_unique<SlushEngine::GameObject>();
    
    SlushEngine::Transform *floor_transform;  
    floor_obj->TryAddComponent<SlushEngine::Transform>(floor_transform, position, scale);
    
    JPH::BoxShapeSettings f(ToJolt(Vector3Multiply(floor_transform->scale, (Vector3){0.5f,0.5f,0.5f})));
    
    auto* floor_mesh = floor_obj->AddComponent<SlushEngine::MeshRenderer>(GenMeshCube(1,1,1), LoadMaterialDefault());
    
    auto* floor_rigidbody = floor_obj->AddComponent<SlushEngine::Rigidbody>(floor_transform, &f, SlushEngine::Core::body_interface, JPH::EMotionType::Static, SlushEngine::Layers::NON_MOVING, JPH::EActivation::DontActivate);
    
    floor_mesh->material.maps[MATERIAL_MAP_ALBEDO].color = color;
    floor_obj->name = std::format("Floor {}", floor_obj->id);
    scene.AddObject(std::move(floor_obj));
}
void SceneSetup(){
    srand(time(0));
    camera_obj->name = "camera";
    camera_cam = camera_obj->AddComponent<SlushEngine::Camera>((Vector3){5,0,5}, 90);
    camera_obj->TryGetComponent<SlushEngine::Transform>();
    camera_obj->TryGetComponent<SlushEngine::Rigidbody>();
    camera_obj->TryGetComponent<SlushEngine::MeshRenderer>();
    camera_obj->AddComponent<SlushEngine::Transform>();
    camera_obj->TryGetComponent<SlushEngine::Transform>();
    camera = camera_cam->camera;
    SlushEngine::Core::main_camera = &camera;

    SpawnBox((Vector3){0,-3,0}, (Vector3){50,1,50}, BLACK);
    SpawnBox((Vector3){25,-3,0}, (Vector3){1,500,50}, RED);
    SpawnBox((Vector3){0,-3,25}, (Vector3){50,500,1}, RED);
    SpawnBox((Vector3){-25,-3,0}, (Vector3){1,500,50}, RED);
    SpawnBox((Vector3){0,-3,-25}, (Vector3){50,500,1}, RED);

    sphere_obj = std::make_unique<SlushEngine::GameObject>();
    sphere_transform = sphere_obj->AddComponent<SlushEngine::Transform>((Vector3){5,10,5}, (Vector3){1,1,1});
    JPH::SphereShapeSettings s(sphere_transform->scale.x);
    auto sphere_mesh = sphere_obj->AddComponent<SlushEngine::MeshRenderer>(GenMeshSphere(1,16,16), LoadMaterialDefault());
    sphere_rigidbody = sphere_obj->AddComponent<SlushEngine::Rigidbody>(sphere_transform, &s, SlushEngine::Core::body_interface, JPH::EMotionType::Dynamic, SlushEngine::Layers::MOVING, JPH::EActivation::Activate);
    sphere_mesh->material.maps[MATERIAL_MAP_ALBEDO].color = GREEN;
    sphere_obj->name = std::format("{} {}", "sphere", sphere_obj->id);
    scene.AddObject(std::move(sphere_obj), std::move(camera_obj));
}
void SpawnSphere(){
    auto obj = std::make_unique<SlushEngine::GameObject>();
    float x = ((float)(rand() % 20) / 10) + 0.1;
    int max = 50;
    auto* transform = obj->AddComponent<SlushEngine::Transform>(
                (Vector3){(float)(rand() % max) - 25, (float)(rand() % max), (float)(rand() % max) - 25}, 
                (Vector3){x,x,x});
    JPH::SphereShapeSettings sp(transform->scale.x);
    auto* mesh = obj->AddComponent<SlushEngine::MeshRenderer>(GenMeshSphere(1,16,16), LoadMaterialDefault());
    auto* rigidbody = obj->AddComponent<SlushEngine::Rigidbody>(transform, &sp, SlushEngine::Core::body_interface, JPH::EMotionType::Dynamic, SlushEngine::Layers::MOVING, JPH::EActivation::Activate);
    mesh->material.maps[MATERIAL_MAP_ALBEDO].color = (Color){(unsigned char)(rand() % 255),(unsigned char)(rand() % 255),(unsigned char)(rand() % 255),255};
    obj->name = std::format("{} {}", "Sphere", obj->id);
    scene.AddObject(std::move(obj));
}
void TestBehavior::Start(){
    SceneSetup();
}
bool c = false;
void TestBehavior::Update(float dt){
    if(IsKeyPressed(KEY_TAB)) {
        c ? DisableCursor() : EnableCursor();
        c = !c;
    }
    Vector2 input = SlushEngine::Input::AsVector2Composite(KEY_W, KEY_S, KEY_A, KEY_D);
    SlushEngine::Core::body_interface->SetPosition(sphere_rigidbody->body->GetID(),  ToJolt(camera.position), JPH::EActivation::DontActivate);
    if(IsKeyDown(KEY_SPACE)){
        for(int i = 0; i < 5; i++)
            SpawnSphere();
    } 
}
