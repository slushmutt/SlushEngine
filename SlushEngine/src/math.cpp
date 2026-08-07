#include <SlushEngine/math.h>
#include <raylib.h>
#include <raymath.h>
#include <Jolt/Jolt.h>
#include <Jolt/Math/Vec3.h>
#include <Jolt/Math/Quat.h>

namespace SlushEngine {

    Matrix::Matrix(const ::Matrix& mat) {
        m0 = mat.m0; m4 = mat.m4; m8 = mat.m8; m12 = mat.m12;
        m1 = mat.m1; m5 = mat.m5; m9 = mat.m9; m13 = mat.m13;
        m2 = mat.m2; m6 = mat.m6; m10 = mat.m10; m14 = mat.m14;
        m3 = mat.m3; m7 = mat.m7; m11 = mat.m11; m15 = mat.m15;
    }

    Matrix& Matrix::operator=(const ::Matrix& mat) {
        m0 = mat.m0; m4 = mat.m4; m8 = mat.m8; m12 = mat.m12;
        m1 = mat.m1; m5 = mat.m5; m9 = mat.m9; m13 = mat.m13;
        m2 = mat.m2; m6 = mat.m6; m10 = mat.m10; m14 = mat.m14;
        m3 = mat.m3; m7 = mat.m7; m11 = mat.m11; m15 = mat.m15;
        return *this;
    }

    Matrix::operator ::Matrix() const {
        ::Matrix mat;
        mat.m0 = m0; mat.m4 = m4; mat.m8 = m8; mat.m12 = m12;
        mat.m1 = m1; mat.m5 = m5; mat.m9 = m9; mat.m13 = m13;
        mat.m2 = m2; mat.m6 = m6; mat.m10 = m10; mat.m14 = m14;
        mat.m3 = m3; mat.m7 = m7; mat.m11 = m11; mat.m15 = m15;
        return mat;
    }

    Vector3::Vector3(const ::Vector3& vec) : x(vec.x), y(vec.y), z(vec.z) {}
    
    Vector3::Vector3(const JPH::Vec3& vec) : x(vec.GetX()), y(vec.GetY()), z(vec.GetZ()) {}

    Vector3& Vector3::operator=(const ::Vector3& vec) {
        x = vec.x; y = vec.y; z = vec.z;
        return *this;
    }

    Vector3& Vector3::operator=(const JPH::Vec3& vec) {
        x = vec.GetX(); y = vec.GetY(); z = vec.GetZ();
        return *this;
    }

    Vector3::operator ::Vector3() const {
        return ::Vector3{ x, y, z };
    }

    Vector3::operator JPH::Vec3() const {
        return JPH::Vec3(x, y, z);
    }
    Vector3 Vector3::forward = Vector3(0,0,1);
    Vector3 Vector3::right = Vector3(1,0,0);

    Quaternion::Quaternion(const ::Vector4& q) 
        : x(q.x), y(q.y), z(q.z), w(q.w) {}
    
    Quaternion::Quaternion(const JPH::Quat& q) 
        : x(q.GetX()), y(q.GetY()), z(q.GetZ()), w(q.GetW()) {}

    Quaternion& Quaternion::operator=(const ::Vector4& q) {
        x = q.x; y = q.y; z = q.z; w = q.w;
        return *this;
    }

    Quaternion& Quaternion::operator=(const JPH::Quat& q) {
        x = q.GetX(); y = q.GetY(); z = q.GetZ(); w = q.GetW();
        return *this;
    }

    Quaternion::operator ::Vector4() const {
        return ::Vector4{ x, y, z, w };
    }

    Quaternion::operator JPH::Quat() const {
        return JPH::Quat(x, y, z, w);
    }

    Vector2::Vector2(const ::Vector2& vec) : x(vec.x), y(vec.y) {}

    Vector2& Vector2::operator=(const ::Vector2& vec) {
        x = vec.x; y = vec.y;
        return *this;
    }

    Vector2::operator ::Vector2() const {
        return ::Vector2{ x, y };
    }
}
