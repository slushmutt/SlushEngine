#include <SlushEngine/Components/game_object.h>
#include <SlushEngine/Components/component.h>
#include <SlushEngine/core.h>
#include <SlushEngine/debug.h>
#include <format>
#include <unordered_map>
#include <typeindex>
SlushEngine::GameObject::GameObject(){
    id = SlushEngine::Core::GetUniqueId();
    name = std::format("Object{}", id);
}
SlushEngine::GameObject::~GameObject(){
    Components.clear();
}

std::unordered_map<std::type_index, std::shared_ptr<SlushEngine::Component>>& SlushEngine::GameObject::GetComponents(){
    return Components;
}


