#pragma once
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <SlushEngine/debug.h>
#include <SlushEngine/Components/component.h>
#include <SlushEngine/Utility/type_extension.h>
#include <SlushEngine/export.hpp>
namespace SlushEngine{
    class SLUSH_EXPORT GameObject{
        private:
            std::unordered_map<std::type_index, std::shared_ptr<Component>> Components;
        public:
            std::string name;
            uint32_t id;
            GameObject();
            virtual ~GameObject();
            std::unordered_map<std::type_index, std::shared_ptr<Component>>& GetComponents();
            template<typename T>
            bool TryGetComponent(T*& t){
                static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
                auto it = Components.find(typeid(T));
                if(it != Components.end()) {
                    t = static_cast<T*>(it->second.get());
                    return true;
                }
                SlushEngine::Debug::Error("{} is not found on {} Id: {}.", get_type_name<T>(), name, id);
                return false;
            }
            template<typename T>
            bool TryGetComponent() {
                static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
                bool b = Components.contains(std::type_index(typeid(T)));
                b ? void() : SlushEngine::Debug::Error("{} is not found on {} Id: {}.", get_type_name<T>(), name, id);
                return b;
            }
            template<typename T>
            T* GetComponent(){
                static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
                auto it = Components.find(typeid(T));
                if(it != Components.end()) {
                    return static_cast<T*>(it->second.get());
                }
                SlushEngine::Debug::Error("{} is not found on {} Id: {}.", get_type_name<T>(), name, id);
                return nullptr;
            }
            template <typename T, typename... Args>
            bool TryAddComponent(T *&t, Args&&... args) {
                if(Components.contains(std::type_index(typeid(T))) || t == nullptr){ 
                    SlushEngine::Debug::Error("{} is already on {} Id: {}.", get_type_name<T>(), name, id);
                    return false;
                }

                auto newComp = std::make_shared<T>(std::forward<std::decay_t<Args>>(args)...);
                newComp->owner = this; 
                T* ptr = newComp.get();
                if(!Components.emplace(std::type_index(typeid(T)),(newComp)).second){
                    SlushEngine::Debug::Error("Failed to add {} to {} Id: {}!", get_type_name<T>(), name, id);
                    return false;
                }
                t = ptr;
                SlushEngine::Debug::Success("Successfully added {} to {} Id: {}", get_type_name<T>(), name, id);
                return true;
            }
            template <typename T, typename... Args>
            T* AddComponent(Args&&... args) {
                Components.contains(std::type_index(typeid(T))) ? 
                    SlushEngine::Debug::Error("{} already on {} Id: {}.", get_type_name<T>(), name, id) 
                : void();   

                auto newComp = std::make_shared<T>(std::forward<Args>(args)...);
                newComp->owner = this; 
                T* ptr = newComp.get();
                Components.emplace(std::type_index(typeid(T)),(newComp));
                return ptr;
            }




    };
}
