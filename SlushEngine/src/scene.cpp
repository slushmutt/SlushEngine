#include <SlushEngine/scene.h>
#include <SlushEngine/Components/component.h>
#include <SlushEngine/Components/game_object.h>
#include <SlushEngine/Components/transform.h>
#include <SlushEngine/core.h>
#include <SlushEngine/Utility/raylib_extensions.h>

SlushEngine::Scene::Scene(){
    SlushEngine::Core::active_scenes.push_back(this);
}
SlushEngine::Scene::~Scene(){
    std::erase(SlushEngine::Core::active_scenes, this);
}

std::vector<std::unique_ptr<SlushEngine::GameObject>>& SlushEngine::Scene::GetObjects(){
    return objects;
}
void SlushEngine::Scene::Update(float dt){
    for(auto &obj: objects) {
        for(const auto &component: obj->GetComponents()){
            component.second->Update(dt);
        }
    }
}
void SlushEngine::Scene::PhysicsUpdate(){
    for(auto &obj: objects) {
        for(const auto &component: obj->GetComponents()){
            component.second->PhysicsUpdate();
        }
    }
}

void SlushEngine::Scene::Start(){
    for(auto &obj: objects) {
        for(const auto &component: obj->GetComponents()){
            component.second->Start();
        }
    }
}

void SlushEngine::Scene::Awake(){
    for(auto &obj: objects) {
        for(const auto &component: obj->GetComponents()){
            component.second->Awake();
        }
    }
}
