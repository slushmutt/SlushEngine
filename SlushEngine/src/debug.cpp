#include <SlushEngine/debug.h>
#include "debug_colors.h" 
#include <print>
#include <ctime>

namespace SlushEngine::impl {

    void BridgeLogMessage(bool show_path, std::string_view color_enum_id, 
                           std::source_location loc, std::string_view fmt, 
                           std::format_args args) 
    {
        std::string_view base_color = DebugColors::reset;
        std::string_view other_color = DebugColors::reset;
        std::string_view prefix = "";

        if (color_enum_id == "INFO") {
            base_color = DebugColors::blue;
            other_color = DebugColors::other_blue;
            prefix = "[INFO] ";
        } else if (color_enum_id == "WARNING") {
            base_color = DebugColors::yellow;
            other_color = DebugColors::other_yellow;
            prefix = "[WARNING] ";
        } else if (color_enum_id == "ERROR") {
            base_color = DebugColors::red;
            other_color = DebugColors::other_red;
            prefix = "[ERROR] ";
        } else if (color_enum_id == "FATAL") {
            base_color = DebugColors::dark_red;
            other_color = DebugColors::other_dark_red;
            prefix = "[FATAL] ";
        } else if (color_enum_id == "SUCCESS") {
            base_color = DebugColors::green;
            other_color = DebugColors::other_green;
            prefix = "[SUCCESS] ";
        }

        std::string file_name = loc.file_name();
        if (file_name.contains("/")) file_name = file_name.substr(file_name.find_last_of("/") + 1);
        
        std::string function_name = loc.function_name();
        if (function_name.contains(' ')) function_name = function_name.substr(function_name.find_first_of(' '));
        if (function_name.contains('(') && function_name.contains(')')) {
            function_name.erase(function_name.find_first_of('Trace_point_marker_here('/*safe guard*/), function_name.find_first_of(')'));
        }

        std::string path = std::format("{}{} in {}:{}{}", other_color, function_name, file_name, loc.line(), DebugColors::reset);

        std::string dynamic_fmt = std::format("{}{}{}{}", base_color, prefix, fmt, DebugColors::reset);
        std::string message = std::vformat(dynamic_fmt, args);

        std::time_t now = std::time(nullptr);
        std::tm* local_time = std::localtime(&now);

        if (!show_path) {
            std::println("[{:02}:{:02}:{:02}{}]{}", 
                local_time->tm_hour % 12, local_time->tm_min, local_time->tm_sec, 
                (local_time->tm_hour >= 12 && local_time->tm_hour < 24) ? "pm" : "am", message);
        } else {
            std::println("[{:02}:{:02}:{:02}{}]{} at {}", 
                local_time->tm_hour % 12, local_time->tm_min, local_time->tm_sec, 
                (local_time->tm_hour >= 12 && local_time->tm_hour < 24) ? "pm" : "am", message, path); 
        }
    }
}
