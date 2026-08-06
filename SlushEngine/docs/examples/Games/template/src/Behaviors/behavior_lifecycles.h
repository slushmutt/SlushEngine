// [Behavior Example]
#include <SlushEngine/behavior.h>
#include <SlushEngine/auto_register.h>
class BehaviorLifecycles: public SlushEngine::Behavior {
    public:
        void Start() override;
        void Awake() override;
        void Update(float dt) override;
};
// [Behavior Example]
