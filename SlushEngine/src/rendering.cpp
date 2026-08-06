#include "SlushEngine/debug.h"
#include <SlushEngine/rendering.h>
#include <SlushEngine/math.h>
#include <cstdlib>
#include <raylib.h>


namespace SlushEngine {
        Texture Texture::Load(std::string path) {
            Texture2D t = LoadTexture(path.c_str());
            return Texture(t.id, t.width, t.height, t.mipmaps, t.format);
        }

        void Mesh::Upload(bool dynamic) {
            Debug::Info("Uploading mesh to GPU.");
            ::Mesh rMesh = static_cast<::Mesh>(*this); 
            UploadMesh(&rMesh, dynamic);               
            *this = rMesh;                             
            Debug::Success("Mesh uploaded. vaoId={}", rMesh.vaoId);
        }

        void Mesh::Draw(Material material, Matrix transform){ 
            ::Mesh m = static_cast<::Mesh>(*this); 
            DrawMesh(m, material, transform);
        }
        Texture::operator ::Texture() const {
            ::Texture r_texture = {0};
            r_texture.format = this->format;
            r_texture.width = this->width;
            r_texture.height = this->height;
            r_texture.mipmaps = this->mipmaps;
            r_texture.id = this->id;
            return r_texture;
        }
        Color::operator ::Color() const{
            ::Color r_color = {0};
            r_color.r = this->r;
            r_color.g = this->g;
            r_color.b = this->b;
            r_color.a = this->a;
            return r_color;
        }

        MaterialMap::operator ::MaterialMap() const {
            ::MaterialMap r_material_map = {0};

            r_material_map.color = this->color;
            r_material_map.texture = this->texture;
            r_material_map.value = this->value;

            return r_material_map;
        }
        MaterialMap::MaterialMap(const ::MaterialMap& mm)
            : texture(mm.texture), color(mm.color.r, mm.color.g, mm.color.b, mm.color.a), value(mm.value) {}

        Shader::operator ::Shader() const {
            ::Shader r_shader = {0};

            r_shader.id = this->id;
            r_shader.locs = this->locs;
            
            return r_shader;
        }

        Material::operator ::Material() const {
            ::Material r_material = {0};
            r_material.shader = this->shader;

            int i = 0;
            for (auto p : this->params) {
                r_material.params[i] = p;
                i++;
            }

            r_material.maps = new ::MaterialMap[12](); 
            if (this->maps != nullptr) {
                for (int x = 0; x < 10; x++) {
                    r_material.maps[x] = static_cast<::MaterialMap>(this->maps[x]); 
                }
            }

            return r_material;
        }
        Texture::Texture(const ::Texture& t) : Texture(t.id, t.width, t.height, t.mipmaps, t.format) {}

        Material::Material(const ::Material& m) {
            shader.id = m.shader.id;
            shader.locs = m.shader.locs;

            maps = new MaterialMap[10]();
            for (int x = 0; x < 10; x++) {
                this->maps[x] = m.maps[x];
            }
            for (int i = 0; i < 4; i++) params[i] = m.params[i];
        }


        Mesh::operator ::Mesh() const {
            ::Mesh rMesh = {0};

            rMesh.vboId = new unsigned int[7]; 
            rMesh.vertexCount = this->vertexCount;
            rMesh.triangleCount = this->triangleCount;
            
            rMesh.vertices = this->vertices;
            rMesh.texcoords = this->texcoords;
            rMesh.texcoords2 = this->texcoords2;
            rMesh.normals = this->normals;
            rMesh.tangents = this->tangents;
            rMesh.colors = this->colors;
            rMesh.indices = this->indices;

            rMesh.boneCount = this->boneCount;
            rMesh.boneIndices = this->boneIndices;
            rMesh.boneWeights = this->boneWeights;

            rMesh.animVertices = this->animVertices;
            rMesh.animNormals = this->animNormals;

            rMesh.vaoId = this->vaoId;

            for (int i = 0; i < 7; i++) {
                if (this->vboId != nullptr) {
                    rMesh.vboId[i] = this->vboId[i];
                } else {
                    rMesh.vboId[i] = 0; 
                }
            }

            return rMesh;
        }

        Mesh& Mesh::operator=(const ::Mesh& rMesh) {
            this->vertexCount = rMesh.vertexCount;
            this->triangleCount = rMesh.triangleCount;

            this->vertices = rMesh.vertices;
            this->texcoords = rMesh.texcoords;
            this->texcoords2 = rMesh.texcoords2;
            this->normals = rMesh.normals;
            this->tangents = rMesh.tangents;
            this->colors = rMesh.colors;
            this->indices = rMesh.indices;

            this->boneCount = rMesh.boneCount;
            this->boneIndices = rMesh.boneIndices;
            this->boneWeights = rMesh.boneWeights;

            this->animVertices = rMesh.animVertices;
            this->animNormals = rMesh.animNormals;

            this->vaoId = rMesh.vaoId;
            
            if (this->vboId == nullptr) {
                this->vboId = new unsigned int[7];
            }

            for (int i = 0; i < 7; i++) {
                if (rMesh.vboId != nullptr) {
                    this->vboId[i] = rMesh.vboId[i];
                } else {
                    this->vboId[i] = 0;
                }
            }

            return *this;
        }
}
