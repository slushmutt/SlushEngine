#pragma once
#include <SlushEngine/Components/component.h>
#include <SlushEngine/export.hpp>
#include <SlushEngine/math.h>
extern "C" {
    typedef struct Camera3D Camera3D;
}


namespace SlushEngine {

    typedef enum {
        CAMERA_CUSTOM = 0,              
        CAMERA_FREE,                    
        CAMERA_ORBITAL,                 
        CAMERA_FIRST_PERSON,            
        CAMERA_THIRD_PERSON             
    } CameraMode;

    typedef enum {
        CAMERA_PERSPECTIVE = 0,         
        CAMERA_ORTHOGRAPHIC             
    } CameraProjection;

    class SLUSH_EXPORT Camera : public Component {

        public: 
            Camera3D* camera = nullptr;
            Vector3 position = { 0.0f, 0.0f, 0.0f };
            Vector3 target = { 5.0f, 0.0f, 0.0f };
            Vector3 up = { 0.0f, 1.0f, 0.0f };
            float fov = 75.0f;
            int projection = CAMERA_PERSPECTIVE;
            int mode = CAMERA_FREE;
            Camera(float fov = 75, Vector3 position = {0,0,0}, Vector3 target = {5,0,0});
            void Awake() override;
            void Start() override;
            void Update(float dt) override;
            void PhysicsUpdate() override;
    };
}

