#include <SlushEngine/behavior.h>
#include <SlushEngine/auto_register.h>
#include <raylib.h>
#include <vector>
namespace SlushEngine {
    class Renderer : public SlushEngine::Behavior, private SlushEngine::AutoRegister<Renderer> {
        void Update(float dt) override;
        public:
            Renderer(){(void)registrar;}
            struct RendererParams{
                Mesh *mesh;
                Material *material;
                Matrix transform;

                bool operator==(const RendererParams& other) const {
                    return mesh->vaoId == other.mesh->vaoId;
                }
            };
            static void AddToRenderQueue(RendererParams params){
                queue.push_back(params);
            };

      private:
            static std::vector<RendererParams> queue;
    };
}
