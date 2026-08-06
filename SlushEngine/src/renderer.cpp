#include <SlushEngine/debug.h>
#include <raylib.h>
#include <renderer.h>
#include <raymath.h>
#include <rlgl.h>
#include <vector>

std::vector<SlushEngine::Renderer::RendererParams> SlushEngine::Renderer::queue;

void SlushEngine::Renderer::Update(float dt) {
    for(auto cmd: queue){
        cmd.mesh->Draw(*cmd.material, cmd.transform);
    }
    queue.clear();
}
