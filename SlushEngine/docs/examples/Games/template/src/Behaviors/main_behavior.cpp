// [Behavior Example]
#include "main_behavior.h"
#include <SlushEngine/Components/camera.h>
#include <SlushEngine/Components/transform.h>
#include <SlushEngine/scene.h>

// Initializing needed variables.

// A scene must be loaded in the global scope of the file
// if it is not it will unload after the function ends which causes the application to crash.
SlushEngine::Scene scene;
// When creating a GameObject it must be a unique pointer.
auto camera_obj = std::make_unique<SlushEngine::GameObject>();
// The camera component.
SlushEngine::Camera *camera_cam;
// Subject to change. (from raylib)
Camera3D camera;

void MainBehavior::Start(){
    // Add the camera component to the camera object. 
    // Initialize values with the constructor.
    camera_cam = camera_obj->AddComponent<SlushEngine::Camera>((Vector3){5,0,5}, 90);
    // A transform is required for a camera to work.
    camera_obj->AddComponent<SlushEngine::Transform>();
    // Get the raylib camera from the camera component. (Subject to change)
    camera = camera_cam->camera;
    // Set the main camera to the newly created camera.
    SlushEngine::Core::main_camera = &camera;

    // Move the camera objects pointer to the scenes object registry.
    scene.AddObject(std::move(camera_obj));
}

// [Behavior Example]
