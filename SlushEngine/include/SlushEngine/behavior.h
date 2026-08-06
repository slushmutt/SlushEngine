#pragma once
#include <SlushEngine/export.hpp>


namespace SlushEngine {
    /**
    * @ingroup core
    * @brief Behaviors are the main class that game scripts will derive from. 
    *
    * Behaviors allow game scripts to use lifecycle functions, such as Start(), Update() and many others.\n
    * Behaviors can be auto loaded at runtime if the class also inherits from AutoRegister. \n
    * The simplest behavior to make an application run properly is seen below: \n
    *
    *  ## main_behavior.h
    * @snippet Games/template/src/Behaviors/main_behavior.h Behavior Example   
    *  ## main_behavior.cpp
    * @snippet Games/template/src/Behaviors/main_behavior.cpp Behavior Example   
    */
    class SLUSH_EXPORT Behavior{
        public:
            /**
             * @brief Update is called every frame.
             *
             * Below is an example of Update and other lifecycles used in a simple way.
             * @snippet Games/template/src/Behaviors/behavior_lifecycles.cpp Behavior Example   
             *
             * @param dt The amount of time between the last frame and the current (Delta Time).
             */
            virtual void Update(float dt);
            /**
             * @brief Physics Update is called every physics tick (by default that is once every 60th of a second).
             *
             */
            virtual void PhysicsUpdate();
            /**
             * @brief Subject to change.
             */
            virtual void RenderUpdate();
            /**
             * @brief Start is called as the final step before the application loop.
             *
             * Below is an example of Start and other lifecycles used in a simple way.
             * @snippet Games/template/src/Behaviors/behavior_lifecycles.cpp Behavior Example   
             */
            virtual void Start();
            /**
             * @brief Awake is called as the first step after the window is initialized.
             *
             * Below is an example of Awake and other lifecycles used in a simple way.
             * @snippet Games/template/src/Behaviors/behavior_lifecycles.cpp Behavior Example   
             */
            virtual void Awake();
    };
}
