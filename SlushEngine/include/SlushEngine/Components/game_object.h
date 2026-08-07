#pragma once
#include <SlushEngine/Components/component.h>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <SlushEngine/export.hpp>
#include <SlushEngine/debug.h>
#include <SlushEngine/rendering.h>
#include <SlushEngine/math.h>
#include <SlushEngine/Utility/type_extension.h>

extern "C" {
    struct Mesh;
}
namespace SlushEngine {
    class Transform;

    enum Primitive{
        Sphere,
        Cylinder,
        Cube,
        Plane
    };

    class SLUSH_EXPORT GameObject {
    public:
        uint32_t id;
        std::string name;
        Transform* transform;

        GameObject();
        ~GameObject();

        std::unordered_map<std::type_index, std::shared_ptr<Component>>& GetComponents();

        template<typename T>
        bool TryGetComponent(T*& t) {
            static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
            auto it = Components.find(typeid(T));
            if(it != Components.end()) {
                t = static_cast<T*>(it->second.get());
                return true;
            }
            Debug::Error("{} is not found on {} Id: {}.", get_type_name<T>(), name, id);
            return false;
        }

        template<typename T>
        bool TryGetComponent() {
            static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
            bool b = Components.contains(std::type_index(typeid(T)));
            b ? void() : Debug::Error("{} is not found on {} Id: {}.", get_type_name<T>(), name, id);
            return b;
        }

        template<typename T>
        T* GetComponent() {
            static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
            auto it = Components.find(typeid(T));
            if(it != Components.end()) {
                return static_cast<T*>(it->second.get());
            }
            Debug::Error("{} is not found on {} Id: {}.", get_type_name<T>(), name, id);
            return nullptr;
        }

        template <typename T, typename... Args>
        bool TryAddComponent(T *&t, Args&&... args) {
            if(Components.contains(std::type_index(typeid(T))) || t == nullptr) { 
                Debug::Error("{} is already on {} Id: {}.", get_type_name<T>(), name, id);
                return false;
            }

            auto newComp = std::make_shared<T>(std::forward<std::decay_t<Args>>(args)...);
            newComp->owner = this; 
            T* ptr = newComp.get();
            newComp->Awake();
            if(!Components.emplace(std::type_index(typeid(T)), (newComp)).second) {
                Debug::Error("Failed to add {} to {} Id: {}!", get_type_name<T>(), name, id);
                return false;
            }
            t = ptr;
            Debug::Success("Successfully added {} to {} Id: {}", get_type_name<T>(), name, id);
            return true;
        }

        template <typename T, typename... Args>
        T* AddComponent(Args&&... args) {
            Components.contains(std::type_index(typeid(T))) ? 
                Debug::Error("{} already on {} Id: {}.", get_type_name<T>(), name, id) 
            : void();   

            auto newComp = std::make_shared<T>(std::forward<Args>(args)...);
            newComp->owner = this; 

            T* ptr = newComp.get();

            newComp->Awake();
            Components.emplace(std::type_index(typeid(T)), (newComp));
            return ptr;
        }


        static void InitalizePrimitives();
        static GameObject& CreatePrimitive(Primitive primitive, Color color, Vector3 position = Vector3(), Vector3 scale = Vector3(1,1,1), Quaternion rotation = Quaternion(0,0,0,1));

    private:
        std::unordered_map<std::type_index, std::shared_ptr<Component>> Components;
    };
}
