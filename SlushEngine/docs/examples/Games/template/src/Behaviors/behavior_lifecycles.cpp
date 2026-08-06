// [Behavior Example]
#include "behavior_lifecycles.h"
#include "SlushEngine/debug.h"
#include <SlushEngine/Components/camera.h>
#include <SlushEngine/Components/transform.h>
#include <SlushEngine/scene.h>

float update;

void BehaviorLifecycles::Awake(){
    SlushEngine::Debug::Log("Ran first!");
    update = 0.0f;
}
void BehaviorLifecycles::Start(){
    SlushEngine::Debug::Log("Ran second!");
}
void BehaviorLifecycles::Update(float dt){
    update += dt;
    if(update > 1.0f) {
        SlushEngine::Debug::Log("One second has passed!");
        update = 0.0f;
    }
}
// [Behavior Example]
