#include <memory>
#include <print>
#include <raylib.h>
#include "application.h"
#include "Components/game_object.h"
#include "core.h"
#include "input.h"
#include "scene.h"
#include "Components/mesh_renderer.h"
#include "Components/transform.h"
#include "Utility/raylib_extensions.h"

void SlushEngine::Application::Initialize(int width, int height, int fps, const char *window_title){
    InitWindow(width, height, window_title);
    SetTargetFPS(fps);
    Loop();
}

void SlushEngine::Application::Loop(){
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 0.0f, 20.0f};  
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };     
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };        
    camera.fovy = 45.0f;                                
    camera.projection = CAMERA_PERSPECTIVE;            

    Scene new_scene;
    auto obj = std::make_unique<GameObject>();
    obj->name = "hello";

    Transform *transform = obj->AddComponent<Transform>();   
    transform->position.x = 0;
    transform->position.y = 0;
    transform->position.z = 0;
    
    MeshRenderer *mesh_renderer = obj->AddComponent<MeshRenderer>();
    mesh_renderer->mesh = GenMeshCube(5,5,5);
    mesh_renderer->material = LoadMaterialDefault();
    mesh_renderer->material.maps[MATERIAL_MAP_ALBEDO].color = BLACK;

    new_scene.AddObject(std::move(obj));

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        transform->Rotate(0, 1, 0);
        std::println("Rotation in euler angles is: {}", transform->EulerAngles(true));
        for(Scene *scene: SlushEngine::Core::active_scenes){
            scene->Update(0);
        }
        EndDrawing();
        EndMode3D();
    }
    CloseWindow();
}
