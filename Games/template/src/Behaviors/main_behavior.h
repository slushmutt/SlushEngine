#include <SlushEngine/behavior.h>
#include <SlushEngine/auto_register.h>
class MainBehavior : public SlushEngine::Behavior, private SlushEngine::AutoRegister<MainBehavior> {
    public:
        MainBehavior(){(void)registrar;}
        void Update(float dt) override;
        void Start() override;
};
