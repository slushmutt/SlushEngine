#include <cstdlib>
#include <ctime>
#include <format>
#include <print>
#include <raylib.h>
#include "application.h"
#include <rlImGui.h>
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
#include "Jolt/Physics/Body/BodyInterface.h"
#include "SlushEngine/debug.h"
#include "core.h"
#include "imgui.h"
#include "input.h"
#include "scene.h"
#include "Utility/raylib_extensions.h"
#include "physics.h"
#include "behavior.h"
#include "Components/game_object.h"
#include "Components/component.h"
#include "Components/transform.h"

void DebugWindow() {
    bool is_visible = ImGui::Begin("Debug");
    if (is_visible) 
    {
        if (SlushEngine::Core::active_scenes.empty()) {
            ImGui::Text("No active scenes loaded.");
        }
        else 
        {
            static int selected_idx = 0;                                                                                                                   
            if (ImGui::BeginListBox("Physics Objects", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()))){
                auto& objects = SlushEngine::Core::active_scenes.front()->GetObjects(); 
                for(size_t n = 0; n < objects.size(); n++) {
                    const bool is_selected = (selected_idx == n);
                    ImGui::PushID(n);
                    if (ImGui::Selectable(objects[n]->name.c_str(), is_selected)) {
                        selected_idx = n;
                    }
                    
                    if (is_selected) {          
                        ImGui::SetItemDefaultFocus();                                                                                                                                                                           
                        auto pos = objects[selected_idx]->GetComponent<SlushEngine::Transform>()->position;
                        auto scale = objects[selected_idx]->GetComponent<SlushEngine::Transform>()->scale;
                        ImGui::TextUnformatted(std::format("{}",pos).c_str());
                    }                                                                                                                                                                                                           
                    ImGui::PopID();                                                                                                                                                                                         
                }                                                                                                                                                                                           
                ImGui::EndListBox();                                                                                                                                                                        
            }
        }
    }
    ImGui::End();
}


void SlushEngine::Application::Initialize(int width, int height, int fps, const char *window_title){
    SetTraceLogLevel(LOG_FATAL); 
    // check for most deadly issues that are hard to debug.
    SlushEngine::Core::active_behaviors.size() <= 0 ? SlushEngine::Debug::Fatal("No behaviors found, aborting...") : SlushEngine::Debug::Success("At least one behavior was loaded!"); 
    SlushEngine::Core::active_scenes.size() <= 0 ? SlushEngine::Debug::Fatal("No scenes found, aborting...") : SlushEngine::Debug::Success("At least one scene was loaded!"); 
    srand(time(0)); // generate random seed for random numbers.
    JPH::RegisterDefaultAllocator(); // allocate default memory for the physics system.
    InitWindow(width, height, window_title);
    SlushEngine::Debug::Info("SlushEngine window created.");
    rlImGuiSetup(true);
    SlushEngine::Debug::Info("rlImGui loaded successfully.");
    SetTargetFPS(fps);

    //running awake on all game scripts and Components.
    for(auto *behavior: SlushEngine::Core::active_behaviors){
            behavior->Awake();
        }
        for(Scene *scene: SlushEngine::Core::active_scenes){
            scene->Awake();
        }
    // start the game loop
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

        UpdateCamera(SlushEngine::Core::main_camera, CAMERA_FREE);
        while (physics_accumulator >= c_delta_time)
        {
            physics_system.Update(c_delta_time, 1, &temp_allocator, &job_system);
            physics_accumulator -= c_delta_time;
        }

        BeginDrawing();
        rlImGuiBegin();

        // 3d setup
        BeginMode3D(*SlushEngine::Core::main_camera);
        ClearBackground(RAYWHITE);
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
        DebugWindow();
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
