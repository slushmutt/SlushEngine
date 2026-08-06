#pragma once
#include <SlushEngine/export.hpp>
#include <SlushEngine/math.h>
#include <string>

extern "C"{
    struct Color;
    struct Texture;
    struct Mesh;
    struct Material;
    struct MaterialMap;
    struct Shader;
}

namespace SlushEngine {
    struct Color {
        unsigned char r;        
        unsigned char g;        
        unsigned char b;        
        unsigned char a;        

        Color() : r(0), g(0), b(0), a(255) {}
        Color(unsigned char R,unsigned char G,unsigned char B,unsigned char A){
            r = R;
            g = G;
            b = B;
            a = A;
        }
        operator ::Color() const;
    };

    struct Texture {
        unsigned int id;        
        int width;              
        int height;             
        int mipmaps;            
        int format;             

        Texture() : id(0), width(0), height(0), mipmaps(0), format(0) {}   
        Texture(unsigned int i, int w, int h, int m, int f){
            id = i;
            width = w;
            height = h;
            mipmaps = m;
            format = f;
        }
        Texture(const ::Texture& t); 
        static Texture Load(std::string path);

        operator ::Texture() const;
    };

    struct Shader {
        unsigned int id;        
        int *locs;              

        operator ::Shader() const;

    };
    struct MaterialMap {
        Texture texture;      
        Color color;            
        float value;            

        MaterialMap() = default; 
        operator ::MaterialMap() const;
        MaterialMap(const ::MaterialMap& mm);

    };
    struct Material {
        Shader shader;          
        MaterialMap *maps;      
        float params[4];        
        Material() = default;
        operator ::Material() const;
        Material(const ::Material& m);

    };

    typedef enum {
        MATERIAL_MAP_ALBEDO = 0,        
        MATERIAL_MAP_METALNESS,         
        MATERIAL_MAP_NORMAL,            
        MATERIAL_MAP_ROUGHNESS,         
        MATERIAL_MAP_OCCLUSION,         
        MATERIAL_MAP_EMISSION,          
        MATERIAL_MAP_HEIGHT,            
        MATERIAL_MAP_CUBEMAP,           
        MATERIAL_MAP_IRRADIANCE,        
        MATERIAL_MAP_PREFILTER,         
        MATERIAL_MAP_BRDF               
    } MaterialMapIndex;

    struct Mesh {
        int vertexCount;        
        int triangleCount;      

        float *vertices;        
        float *texcoords;       
        float *texcoords2;      
        float *normals;         
        float *tangents;        
        unsigned char *colors;  
        unsigned short *indices; 

        int boneCount;          
        unsigned char *boneIndices; 
        float *boneWeights;     
            
        float *animVertices;    
        float *animNormals;     

        unsigned int vaoId;     
        unsigned int *vboId;    

        operator ::Mesh() const;

        Mesh& operator=(const ::Mesh& rMesh);

        void Upload(bool dynamic);
        void Draw(Material material, SlushEngine::Matrix transform);
    };

    class SLUSH_EXPORT Rendering {

    };     
}
