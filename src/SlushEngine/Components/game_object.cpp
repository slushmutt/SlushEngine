#include "game_object.h"
#include "../core.h"
#include "component.h"
#include <format>
#include <unordered_map>
#include <typeindex>
SlushEngine::GameObject::GameObject(){
    id = SlushEngine::Core::GetUniqueId();
    name = std::format("Object: {}", id);
}

std::unordered_map<std::type_index, std::unique_ptr<SlushEngine::Component>>& SlushEngine::GameObject::GetComponents(){
    return Components;
}


