#pragma once
#include <string_view>

namespace DebugColors {
    inline constexpr std::string_view reset          = "\x1b[0m";
    inline constexpr std::string_view red            = "\x1b[31m";
    inline constexpr std::string_view other_red      = "\x1b[38;5;203m";
    inline constexpr std::string_view dark_red       = "\x1b[38;5;88m\x1b[47m";
    inline constexpr std::string_view other_dark_red = "\x1b[38;5;124m\x1b[47m";
    inline constexpr std::string_view green          = "\x1b[32m";
    inline constexpr std::string_view other_green    = "\x1b[38;5;157m";
    inline constexpr std::string_view yellow         = "\x1b[33m";
    inline constexpr std::string_view other_yellow   = "\x1b[38;5;229m\x1b[33m";
    inline constexpr std::string_view blue           = "\x1b[34m";
    inline constexpr std::string_view other_blue     = "\x1b[38;5;111m";
}
