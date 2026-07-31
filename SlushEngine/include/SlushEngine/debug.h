#pragma once

#include <cstdlib>
#include <format>
#include <iostream>
#include <print>
#include <source_location>
#include <string>
#include <string_view>
#include <utility>
#include <SlushEngine/debug_colors.h>
#include <SlushEngine/export.hpp>
namespace SlushEngine {
        namespace impl {

            template<typename T>
            std::string to_str(const T& val){
                return std::to_string(val);
            }

            inline std::string to_str(const std::string& val){
                return val;
            }

            inline std::string to_str(const char * str){
                return std::string(str);
            }


            struct LogFormat {
                std::string_view fmt;
                std::source_location loc;
                bool path = true;

                LogFormat(const char* s, std::source_location l = std::source_location::current())
                    : fmt(s), loc(l) {}
        
                LogFormat(std::string_view s, std::source_location l = std::source_location::current())
                    : fmt(s), loc(l) {}

                LogFormat(const std::string& s, std::source_location l = std::source_location::current())
                    : fmt(s), loc(l) {}            
            };

            template <typename... T>
            void LogMessage(bool show_path, std::string color, std::source_location loc, std::string_view fmt, T&&... args) {
                std::string file_name = loc.file_name();
                file_name = file_name.substr(file_name.find_last_of("/") + 1);
                std::string function_name = loc.function_name();
                function_name = function_name.substr(function_name.find_first_of(' '));
                function_name.erase(function_name.find_first_of('('), function_name.find_first_of(')'));

                std::string path = std::format("{}{} in {}:{}{}", color, function_name,
                 file_name, loc.line(), DebugColors::reset);

                auto format_args =  std::make_format_args(args...);
                std::string message = std::vformat(fmt, format_args);
                std::time_t now = std::time(nullptr);
                std::tm* local_time = std::localtime(&now);
                !show_path ? std::println("[{:02}:{:02}:{:02}{}]{}", 
                        local_time->tm_hour % 12, local_time->tm_min, local_time->tm_sec, local_time->tm_hour > 12 && local_time->tm_hour < 24 ? "pm" : "am", message) : std::println("[{:02}:{:02}:{:02}{}]{} at{}", 
                        local_time->tm_hour % 12, local_time->tm_min, local_time->tm_sec, local_time->tm_hour > 12 && local_time->tm_hour < 24 ? "pm" : "am", message, path); 
            }
        }  // namespace impl

        class SLUSH_EXPORT Debug {
            public:
            enum LogLevel{
                LogLevelNone = 6,
                LogLevelFatal = 5,
                LogLevelError = 4,
                LogLevelWarning = 3,
                LogLevelInfo = 2,
                LogLevelAll= 1
            };
            static inline LogLevel LogLevel;

            template <typename... T>
            static void Log(impl::LogFormat format_with_loc, T&&... args) {
              impl::LogMessage(false, DebugColors::reset, format_with_loc.loc, format_with_loc.fmt, std::forward<T>(args)...);
            }

            template <typename... T>
            static void Info(impl::LogFormat format_with_loc, T&&... args) {
                std::string dynamic_fmt = std::format("{}{}{}{}", 
                DebugColors::blue, "[INFO] ", format_with_loc.fmt, DebugColors::reset);

                if(LogLevel <= 2)
                    impl::LogMessage(false, DebugColors::other_blue, format_with_loc.loc, dynamic_fmt, std::forward<T>(args)...);        
            }

            template <typename... T>
            static void Warning(impl::LogFormat format_with_loc, T&&... args) {
                std::string dynamic_fmt = std::format("{}{}{}{}", 
                DebugColors::yellow, "[WARNING] ", format_with_loc.fmt, DebugColors::reset);


                if(LogLevel <= 3)
                    impl::LogMessage(false, DebugColors::other_yellow, format_with_loc.loc, dynamic_fmt, std::forward<T>(args)...);        
            }

            template <typename... T>
            static void Error(impl::LogFormat format_with_loc, T&&... args) {
                std::string dynamic_fmt = std::format("{}{}{}{}", 
                DebugColors::red, "[ERROR] ", format_with_loc.fmt, DebugColors::reset);

                if(LogLevel <= 4)
                    impl::LogMessage(true, DebugColors::other_red, format_with_loc.loc, dynamic_fmt, std::forward<T>(args)...);        
            }
            template <typename... T>
            static void Fatal(impl::LogFormat format_with_loc, T&&... args) {
                std::string dynamic_fmt = std::format("{}{}{}{}", 
                DebugColors::dark_red, "[FATAL] ", format_with_loc.fmt, DebugColors::reset);


                if(LogLevel <= 5)
                    impl::LogMessage(true, DebugColors::other_dark_red, format_with_loc.loc, dynamic_fmt, std::forward<T>(args)...);        
                abort();
            }

            template <typename... T>
            static void Success(impl::LogFormat format_with_loc, T&&... args) {
                std::string dynamic_fmt = std::format("{}{}{}{}", 
                DebugColors::green, "[SUCCESS] ", format_with_loc.fmt, DebugColors::reset);

                if(LogLevel <= 1)
                    impl::LogMessage(false, DebugColors::other_green, format_with_loc.loc, dynamic_fmt, std::forward<T>(args)...);        
            }

        };  
}
