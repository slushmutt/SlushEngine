#pragma once
#include <memory>
#include <vector>
#include "component.h"
class GameObject{
    private:
        std::vector<std::unique_ptr<Component>> Components;
    public:
        GameObject();
        template<typename T, typename... Args>
        T& AddComponent(Args&&... args);

        template<typename T>
        T* GetComponent(){
            static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
            for (auto& component : Components) {
                if (auto* casted = dynamic_cast<T*>(component.get()))
                {
                    //**
                    //Getting components might be a bit bad with performance,
                    //I didn't want to do a dynamic cast but it was the only solution I could think of.
                    //I'd honestly just test it.
                    //**


                    return casted;
                }
            }

            return nullptr;
        }


};

