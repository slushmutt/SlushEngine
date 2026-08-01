#include <raylib.h>
#include <rendering.h>
#include <vector>

std::vector<Renderer::RendererParams> Renderer::queue;

void Renderer::Update(float dt){
    //BeginDrawing();
    for (const RendererParams& cmd : queue)
    {
        DrawMesh(cmd.mesh, cmd.material, cmd.transform);
    }
    queue.clear();
    //EndDrawing();
} 
