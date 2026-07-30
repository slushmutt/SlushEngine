#include "../SlushEngine/behavior.h"
#include "../SlushEngine/auto_register.h"

class TestBehavior: public SlushEngine::Behavior, private SlushEngine::AutoRegister<TestBehavior>{
    public: 
        TestBehavior(){(void)registrar;}
        void Update(float dt) override;
        void Start() override;
};
