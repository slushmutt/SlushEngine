#include "mesh_renderer.h"
#include "transform.h"
#include <raylib.h>
#include <raymath.h>
#include "game_object.h"

SlushEngine::Transform *transform;
void SlushEngine::MeshRenderer::Update(float dt){
    transform = owner->GetComponent<Transform>();
    Matrix rotation = QuaternionToMatrix(transform->rotation);  
    Matrix position = MatrixTranslate(transform->position.x, transform->position.y, transform->position.z);
    Matrix matrix = MatrixMultiply(position, rotation);
    DrawMesh(mesh,material, matrix);
}
void SlushEngine::MeshRenderer::Start(){
}

void SlushEngine::MeshRenderer::Awake(){

}
