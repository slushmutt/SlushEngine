#include <SlushEngine/Components/mesh_renderer.h>
#include <SlushEngine/debug.h>
#include <SlushEngine/Components/rigidbody.h>
#include <raylib.h>
#include <raymath.h>
#include <SlushEngine/Components/game_object.h>
#include <SlushEngine/Components/transform.h>
#include <SlushEngine/rendering.h>
#include <renderer.h>
SlushEngine::MeshRenderer::MeshRenderer(Mesh Mesh, Material Material){
    mesh = Mesh;
    material = Material;
}
void SlushEngine::MeshRenderer::Update(float dt){ 
    SlushEngine::Transform *transform; 
    transform = owner->transform;

    Matrix rotation = QuaternionToMatrix(transform->rotation);  
    Matrix position = MatrixTranslate(
            transform->position.x,
            transform->position.y,
            transform->position.z
        );

    Matrix scale = MatrixScale(transform->scale.x, transform->scale.y, transform->scale.z);
    Matrix matrix = MatrixMultiply(MatrixMultiply(scale, rotation), position);
    Renderer::RendererParams Params = {
        &mesh,
        &material,
        matrix
    };

    Renderer::AddToRenderQueue(Params);
}
void SlushEngine::MeshRenderer::Start(){
}

void SlushEngine::MeshRenderer::Awake(){

}
void SlushEngine::MeshRenderer::PhysicsUpdate(){}
