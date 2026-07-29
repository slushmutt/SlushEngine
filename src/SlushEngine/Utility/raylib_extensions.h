#include <format>
#include <raylib.h>
template <>
struct std::formatter<Vector3> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    auto format(const Vector3& p, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "({}, {}, {})", p.x, p.y, p.z);
    }
};
