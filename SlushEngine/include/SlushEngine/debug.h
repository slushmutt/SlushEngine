#pragma once
#include <format>
#include <source_location>
#include <string>
#include <string_view>
#include <SlushEngine/export.hpp>

namespace SlushEngine {
        namespace impl {
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

            SLUSH_EXPORT void BridgeLogMessage(bool show_path, std::string_view color_enum_id, 
                                               std::source_location loc, std::string_view fmt, 
                                               std::format_args args);
        }  // namespace impl

        class SLUSH_EXPORT Debug {
            public:
            enum LogLevel {
                LogLevelNone = 6, LogLevelFatal = 5, LogLevelError = 4,
                LogLevelWarning = 3, LogLevelInfo = 2, LogLevelAll = 1
            };
            static inline LogLevel CurrentLogLevel = LogLevelAll; 

            template <typename... T>
            static void Log(impl::LogFormat f, T&&... args) {
                impl::BridgeLogMessage(false, "RESET", f.loc, f.fmt, std::make_format_args(args...));
            }

            template <typename... T>
            static void Info(impl::LogFormat f, T&&... args) {
                if(CurrentLogLevel <= 2)
                    impl::BridgeLogMessage(true, "INFO", f.loc, f.fmt, std::make_format_args(args...));        
            }

            template <typename... T>
            static void Warning(impl::LogFormat f, T&&... args) {
                if(CurrentLogLevel <= 3)
                    impl::BridgeLogMessage(false, "WARNING", f.loc, f.fmt, std::make_format_args(args...));        
            }

            template <typename... T>
            static void Error(impl::LogFormat f, T&&... args) {
                if(CurrentLogLevel <= 4)
                    impl::BridgeLogMessage(true, "ERROR", f.loc, f.fmt, std::make_format_args(args...));        
            }

            template <typename... T>
            static void Fatal(impl::LogFormat f, T&&... args) {
                if(CurrentLogLevel <= 5)
                    impl::BridgeLogMessage(true, "FATAL", f.loc, f.fmt, std::make_format_args(args...));        
                abort();
            }

            template <typename... T>
            static void Success(impl::LogFormat f, T&&... args) {
                if(CurrentLogLevel <= 1)
                    impl::BridgeLogMessage(false, "SUCCESS", f.loc, f.fmt, std::make_format_args(args...));        
            }
        };  
}
