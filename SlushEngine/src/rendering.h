#include <SlushEngine/behavior.h>
#include <SlushEngine/auto_register.h>
#include <raylib.h>
#include <vector>
class Renderer : public SlushEngine::Behavior, private SlushEngine::AutoRegister<Renderer> {
    void Update(float dt) override;
    public:
        Renderer(){(void)registrar;}
        struct RendererParams{
            Mesh mesh;
            Material material;
            Matrix transform;
        };
        static void AddToRenderQueue(RendererParams params){
            queue.push_back(params);
        };

  private:
        static std::vector<RendererParams> queue;
};
