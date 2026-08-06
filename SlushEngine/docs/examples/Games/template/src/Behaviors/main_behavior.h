// [Behavior Example]
#include <SlushEngine/behavior.h>
#include <SlushEngine/auto_register.h>

class MainBehavior : public SlushEngine::Behavior, private SlushEngine::AutoRegister<MainBehavior> {
    public:
        // Required to allow the Behavior to auto register at runtime.
        MainBehavior(){(void)registrar;}

        void Start() override;
};
// [Behavior Example]
