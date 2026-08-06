#include <cstdlib>
#include <ctime>
#include <raylib.h>
#include <rlImGui.h>
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
#include "Jolt/Physics/Body/BodyInterface.h"
#include "SlushEngine/Components/camera.h"
#include <SlushEngine/application.h>
#include <SlushEngine/Components/game_object.h>
#include <SlushEngine/Components/rigidbody.h>
#include <SlushEngine/debug.h>
#include <SlushEngine/core.h>
#include <SlushEngine/input.h>
#include <SlushEngine/scene.h>
#include <SlushEngine/physics.h>
#include <SlushEngine/behavior.h>

void SlushEngine::Application::Initialize(int width, int height, int fps, const char *window_title){
    TraceLogLevel(LOG_NONE);
    // check for most deadly issues that are hard to debug.
    SlushEngine::Core::active_behaviors.size() <= 0 ? SlushEngine::Debug::Fatal("No behaviors found, aborting...") : void(); 
    SlushEngine::Core::active_scenes.size() <= 0 ? SlushEngine::Debug::Fatal("No scenes found, aborting...") : void(); 
    srand(time(0)); // generate random seed for random numbers.
    JPH::RegisterDefaultAllocator(); // allocate default memory for the physics system.
    SetConfigFlags(FLAG_FULLSCREEN_MODE);  
    InitWindow(width, height, window_title);
    //running awake on all game scripts and Components.
    for(auto *behavior: SlushEngine::Core::active_behaviors){
            behavior->Awake();
        }
        for(Scene *scene: SlushEngine::Core::active_scenes){
            scene->Awake();
        }
    SlushEngine::Debug::Info("SlushEngine window created.");
    rlImGuiSetup(true);
    SlushEngine::Debug::Info("rlImGui loaded successfully.");
    SetTargetFPS(fps);


    // start the game loop
    GameObject::InitalizePrimitives();
    Loop();
}

void SlushEngine::Application::Loop(){
    // Initialize the physics system
    JPH::Factory::sInstance = new JPH::Factory();
    JPH::RegisterTypes();

    JPH::TempAllocatorImpl temp_allocator(10 * 1024 * 1024);
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
    SlushEngine::Debug::Info("Physics Engine intialized properly.");

    // calling start on all behaviors and components.
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

        while (physics_accumulator >= c_delta_time)
        {
            physics_system.Update(c_delta_time, 1, &temp_allocator, &job_system);
            physics_accumulator -= c_delta_time;
        }

        BeginDrawing();
        rlImGuiBegin();

        UpdateCamera(Core::main_camera->camera, Core::main_camera->mode);
        // 3d setup
        BeginMode3D(*Core::main_camera->camera);
        ClearBackground(::BLACK);
        // run update and physics update functions on all behaviors and components

        for(auto *behavior: SlushEngine::Core::active_behaviors){
            behavior->Update(c_delta_time);
            behavior->PhysicsUpdate();
        }

        for(Scene *scene: SlushEngine::Core::active_scenes){
            scene->Update(c_delta_time);
            scene->PhysicsUpdate();
        }
        // end 3d rendering, anything past this point rendering wise will have to be 2d/UI or it will not show
        EndMode3D();
        // imgui
        for (auto *behavior: SlushEngine::Core::active_behaviors) {
            behavior->RenderUpdate();
        }
        rlImGuiEnd();
        EndDrawing();

    }
    // clean up memory
    rlImGuiShutdown();
    JPH::UnregisterTypes();
    delete JPH::Factory::sInstance;
    JPH::Factory::sInstance = nullptr;
    CloseWindow();
}
