#pragma once
#include <Jolt/Jolt.h>
#include "Jolt/Math/Vec3.h"
#include <raylib.h>
namespace SlushEngine {
        struct Vector3 {
            float x,y,z;

            Vector3(const ::Vector3& vec) : x(vec.x), y(vec.y), z(vec.z) {}
            Vector3(const JPH::Vec3 vec) : x(vec.GetX()), y(vec.GetY()), z(vec.GetZ()) {}
            Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

            Vector3& operator=(const ::Vector3& vec){
                this->x = vec.x;
                this->y = vec.y;
                this->z = vec.z;
                return *this;
            }
            Vector3& operator=(const JPH::Vec3& vec){
                this->x = vec.GetX();
                this->y = vec.GetY();
                this->z = vec.GetZ();
                return *this;
            }
            operator ::Vector3() const {
                return ::Vector3{x,y,z};
            }
            operator JPH::Vec3() const {
                return JPH::Vec3{x,y,z};
            }
        };
        struct Vector2 {
            float x,y;

            Vector2(const ::Vector2& vec) : x(vec.x), y(vec.y) {}
            Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

            Vector2& operator=(const ::Vector2& vec){
                this->x = vec.x;
                this->y = vec.y;
                return *this;
            }
            operator ::Vector2() const {
                return ::Vector2{x,y};
            }
        };

        struct Quaternion{

        };
}
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
