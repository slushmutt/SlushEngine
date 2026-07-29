#pragma once
#include <cstdint>
#include <memory>
#include <print>
#include <unordered_map>
#include <typeindex>
#include <vector>
#include "component.h"
namespace SlushEngine{
    class GameObject{
        private:
            std::unordered_map<std::type_index, std::unique_ptr<Component>> Components;
        public:
            std::string name;
            uint32_t id;
            GameObject();
            std::unordered_map<std::type_index, std::unique_ptr<Component>>& GetComponents();
            template<typename T>
            T* GetComponent(){
                static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
                auto it = Components.find(typeid(T));
                if(it != Components.end()) {
                    return static_cast<T*>(it->second.get());
                }
                std::println("Component not found on object {} Id: {}, unintended behavior is likely.", name, id);
                return nullptr;
            }
            template <typename T, typename... Args>
            T* AddComponent(Args&&... args) {
                auto newComp = std::make_unique<T>(std::forward<Args>(args)...);
                newComp->owner = this; 
                T* ptr = newComp.get();
                Components.emplace(std::type_index(typeid(T)),std::move(newComp));
                return ptr;
            }




    };
}
