#include <SlushEngine/scene.h>
#include <SlushEngine/Components/component.h>
#include <SlushEngine/Components/game_object.h>
#include <SlushEngine/Components/transform.h>
#include <SlushEngine/core.h>
#include <SlushEngine/Utility/type_extension.h>

SlushEngine::Scene::Scene(){
    SlushEngine::Core::active_scenes.push_back(this);
}
SlushEngine::Scene::~Scene() = default;

SlushEngine::GameObject* SlushEngine::Scene::CreateObject(Vector3 position, Vector3 scale, Quaternion rotation){
    auto obj = std::make_unique<GameObject>();
    obj->transform->position = position;
    obj->transform->scale = scale;
    obj->transform->rotation = rotation;
    AddObject(std::move(obj));
    return objects.back().get();
}
SlushEngine::GameObject* SlushEngine::Scene::CreateObject(SlushEngine::GameObject& obj){
    auto o = std::make_unique<GameObject>(obj);
    AddObject(std::move(o));
    return objects.back().get();
}

template<typename... Args>
bool SlushEngine::Scene::AddObject(std::unique_ptr<GameObject> obj, Args... args){
    objects.push_back(std::move(obj));
    if constexpr (sizeof...(args) > 0) {
        return AddObject(std::forward<Args>(args)...);
    }
    return true;
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
