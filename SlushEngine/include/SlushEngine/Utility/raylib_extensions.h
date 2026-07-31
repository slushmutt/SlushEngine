#include <format>
#include <raylib.h>
#include <Jolt/Jolt.h>
#include "Jolt/Math/Quat.h"
#include "Jolt/Math/Vec3.h"
#include "Jolt/Math/Vec3.h"
template <>
struct std::formatter<Vector3> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    auto format(const Vector3& p, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "({}, {}, {})", p.x, p.y, p.z);
    }
};
inline JPH::Vec3 ToJolt(const ::Vector3& v) {
    return JPH::Vec3{ v.x, v.y, v.z };
}
inline Vector3 ToRayLib(const ::JPH::Vec3& v) {
    return Vector3{ v.GetX(), v.GetY(), v.GetZ() };
}
inline Quaternion ToRayLib(const ::JPH::Quat& q) {
    return Quaternion{ q.GetX(), q.GetY(), q.GetZ(), q.GetW()};
}
