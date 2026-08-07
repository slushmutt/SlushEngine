#include "SlushEngine/rendering.h"
#include <SlushEngine/math.h>
#include <SlushEngine/Components/mesh_renderer.h>
#include <SlushEngine/Components/game_object.h>
#include <SlushEngine/Components/transform.h>
#include <SlushEngine/Components/component.h>
#include <SlushEngine/core.h>
#include <SlushEngine/debug.h>
#include <format>
#include <raylib.h>

namespace SlushEngine {

    GameObject::GameObject() {
        id = Core::GetUniqueId();
        name = std::format("Object{}", id);
        
        transform = AddComponent<Transform>();
    }

    GameObject::~GameObject() {
        Components.clear();
    }

    std::unordered_map<std::type_index, std::shared_ptr<Component>>& GameObject::GetComponents() {
        return Components;
    }



        static Mesh cube_mesh; 
        static Mesh sphere_mesh; 
        static Mesh cylinder_mesh;
        static Mesh plane_mesh;
    void GameObject::InitalizePrimitives(){
        cube_mesh = GenMeshCube(1,1,1);
        cube_mesh.Upload(false);
        sphere_mesh = GenMeshSphere(1,16,16);
        sphere_mesh.Upload(false);
        cylinder_mesh = GenMeshCylinder(1,1,16);
        cylinder_mesh.Upload(false);
        plane_mesh = GenMeshPlane(1,1,1,1);
        plane_mesh.Upload(false);
    }

    GameObject& GameObject::CreatePrimitive(Primitive primitive, Color color, Vector3 position, Vector3 scale, Quaternion rotation) {
        SlushEngine::Mesh selected_mesh; 
        SlushEngine::Material m = LoadMaterialDefault();

        bool c = false;
        switch (primitive) {
            case Cube:   selected_mesh = cube_mesh; break;
            case Sphere: selected_mesh = sphere_mesh; break;
            case Plane: selected_mesh = plane_mesh; break;
            case Cylinder: selected_mesh = cylinder_mesh; c = true; break;
            default:     throw std::invalid_argument("Unsupported primitive type");
        }

        GameObject* obj = new GameObject();
        obj->transform->scale = scale;
        obj->transform->position = position;
        obj->transform->rotation = rotation;
        obj->AddComponent<MeshRenderer>(selected_mesh,m)->material.maps[MATERIAL_MAP_ALBEDO].color = color;
        return *obj;
    }
}
