#pragma once
#include <format>
#include <SlushEngine/export.hpp>
extern "C" {
    struct Vector4; 
    struct Vector3; 
    struct Vector2; 
    struct Matrix; 
}

namespace JPH {
    class Vec3; 
    class Quat; 
}
namespace SlushEngine {

    struct SLUSH_EXPORT Matrix {
        float m0, m4, m8, m12;  
        float m1, m5, m9, m13;  
        float m2, m6, m10, m14;
        float m3, m7, m11, m15; 

        Matrix() : 
            m0(1.0f), m4(0.0f), m8(0.0f), m12(0.0f),
            m1(0.0f), m5(1.0f), m9(0.0f), m13(0.0f),
            m2(0.0f), m6(0.0f), m10(1.0f), m14(0.0f),
            m3(0.0f), m7(0.0f), m11(0.0f), m15(1.0f) {}

        Matrix(const ::Matrix& mat);
        Matrix& operator=(const ::Matrix& mat);

        operator ::Matrix() const;

    };
        struct SLUSH_EXPORT Vector3 {
            float x,y,z;

            Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
            
            Vector3(const ::Vector3& vec);
            Vector3(const JPH::Vec3& vec); 

            Vector3& operator=(const ::Vector3& vec);
            Vector3& operator=(const JPH::Vec3& vec);
            Vector3 operator+(const Vector3 vec){
                Vector3 v;
                v.x = this->x + vec.x;
                v.y = this->y + vec.y;
                v.z = this->z + vec.z;
                return v;
            }
            Vector3 operator-(const Vector3 vec){
                Vector3 v;
                v.x = this->x - vec.x;
                v.y = this->y - vec.y;
                v.z = this->z - vec.z;
                return v;
            }
            Vector3 operator*(const Vector3 vec){
                Vector3 v;
                v.x = vec.x * this->x;
                v.y = vec.y * this->y;
                v.z = vec.z * this->z;
                return v;
            }

            operator ::Vector3() const;
            operator JPH::Vec3() const;
        };


        struct SLUSH_EXPORT Vector2 {
            float x,y;

            Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

            Vector2(const ::Vector2& vec);
            Vector2& operator=(const ::Vector2& vec);
            operator ::Vector2() const;
        };

        struct SLUSH_EXPORT Quaternion{

            float x,y,z,w;

            Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) : x(x), y(y), z(z), w(w) {}
            
            Quaternion(const Vector4& vec);
            Quaternion(const JPH::Quat& vec); 

            Quaternion& operator=(const Vector4& vec);
            Quaternion& operator=(const JPH::Quat& vec);

            operator Vector4() const;
            operator JPH::Quat() const;
        };
}
using Vec3 = SlushEngine::Vector3;
using Vec2 = SlushEngine::Vector2;

template <>
struct std::formatter<SlushEngine::Vector3> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }
    auto format(const SlushEngine::Vector3& p, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "({}, {}, {})", p.x, p.y, p.z);
    }
    auto format(const SlushEngine::Vector2& p, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "({}, {})", p.x, p.y);
    }
};
