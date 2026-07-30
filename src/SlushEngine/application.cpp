#include <cstdlib>
#include <ctime>
#include <memory>
#include <print>
#include <raylib.h>
#include "application.h"
#include "Components/camera.h"
#include "Components/game_object.h"
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
#include <raymath.h>
#include <thread>
#include "Components/mesh_renderer.h"
#include "Components/rigidbody.h"
#include "Jolt/Physics/Body/BodyInterface.h"
#include "Jolt/Physics/Body/MotionType.h"
#include "core.h"
#include "input.h"
#include "scene.h"
#include "Utility/raylib_extensions.h"
#include "physics.h"
#include "behavior.h"
#include "Components/game_object.h"
#include "Components/component.h"
#include "Components/transform.h"
#include "Components/mesh_renderer.h"

void SlushEngine::Application::Initialize(int width, int height, int fps, const char *window_title){
    srand(time(0));
    JPH::RegisterDefaultAllocator();
    InitWindow(width, height, window_title);
    SetTargetFPS(fps);
    for(auto *behavior: SlushEngine::Core::active_behaviors){
            behavior->Awake();
        }
        for(Scene *scene: SlushEngine::Core::active_scenes){
            scene->Awake();
        }
    Loop();
}

void SlushEngine::Application::Loop(){
    JPH::Factory::sInstance = new JPH::Factory();
    JPH::RegisterTypes();

    JPH::TempAllocatorImpl temp_allocator(10 * 8024 * 8024);
    JPH::JobSystemThreadPool job_system(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, std::thread::hardware_concurrency() - 1);
    const uint c_max_bodies = 65536;
    const uint c_num_body_mutexes = 0;
    const uint c_max_body_pairs = 65536;
    const uint c_max_contact_constraints = 10240;

    BPLayerInterfaceImpl phase_layer_interface;
    ObjectVsBroadPhaseLayerFilterImpl object_vs_broadphase_layer_filter;
    ObjectLayerPairFilterImpl object_vs_object_layer_filter;

    JPH::PhysicsSystem physics_system;
    physics_system.Init(c_max_bodies, c_num_body_mutexes, c_max_body_pairs, c_max_contact_constraints, phase_layer_interface, object_vs_broadphase_layer_filter, object_vs_object_layer_filter);
    MyContactListener contact_listener;
    physics_system.SetContactListener(&contact_listener);

    JPH::BodyInterface &body_interface = physics_system.GetBodyInterface();
    SlushEngine::Core::body_interface = &body_interface;
	const float c_delta_time = 1.0f / 60.0f;
	physics_system.OptimizeBroadPhase();

    for(auto *behavior: SlushEngine::Core::active_behaviors){
            behavior->Start();
        }
        for(Scene *scene: SlushEngine::Core::active_scenes){
            scene->Start();
        }

    float physics_accumulator = 0.0f;
    while(!WindowShouldClose()) {
        float dt = GetFrameTime(); 
        
        if (dt > 0.25f) dt = 0.25f; 
        
        physics_accumulator += dt;
        

        UpdateCamera(SlushEngine::Core::main_camera, CAMERA_FREE);
        while (physics_accumulator >= c_delta_time)
        {
            physics_system.Update(c_delta_time, 1, &temp_allocator, &job_system);
            physics_accumulator -= c_delta_time;
        }
        BeginDrawing();
        BeginMode3D(*SlushEngine::Core::main_camera);
        ClearBackground(RAYWHITE);
        for(auto *behavior: SlushEngine::Core::active_behaviors){
            behavior->Update(c_delta_time);
            behavior->PhysicsUpdate();
        }
        for(Scene *scene: SlushEngine::Core::active_scenes){
            scene->Update(c_delta_time);
            scene->PhysicsUpdate();
        }
        EndMode3D();
        DrawFPS(0, 0);
        EndDrawing();
    }
    CloseWindow();
    JPH::UnregisterTypes();
    delete JPH::Factory::sInstance;
    JPH::Factory::sInstance = nullptr;
}
