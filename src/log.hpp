// Logging functionality.
//
// Logs can be generated in four different levels: debug, info, warning and
// error. A log level is set to configure the minimum level that will be
// displayed on screen.

#ifndef LOG_HPP
#define LOG_HPP

#include <chrono>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>

// Configures to display logs with level higher or equal to the given one.
#define LOG_SET_DEBUG() Log::SetLevel(Log::Debug)
#define LOG_SET_INFO() Log::SetLevel(Log::Info)
#define LOG_SET_WARNING() Log::SetLevel(Log::Warning)
#define LOG_SET_ERROR() Log::SetLevel(Log::Error)

#define __CLASS_NAME__ Log::GetClassName(__PRETTY_FUNCTION__)

// Outputs a log message if it's level is high enough.
#define LOG(level, message) \
    do { \
        if (level >= Log::GetLevel()) { \
            Log::GetStream() \
            << Log::GetLevelColor(level) \
            << Log::GetLevelString(level) \
            << " " \
            << Log::GetTime() \
            << " (" \
            << Log::GetFilename(__FILE__) \
            << ":" \
            << __LINE__ \
            << ") [" \
            << __CLASS_NAME__ \
            << "] " \
            << message \
            << Log::GetResetColor() \
            << "\n"; \
        } \
    } while (false)

// Outputs debug log message.
#define LOG_D(message) LOG(Log::Debug, message)

// Outputs informational log message.
#define LOG_I(message) LOG(Log::Info, message)

// Outputs warning log message.
#define LOG_W(message) LOG(Log::Warning, message)

// Outputs error log message.
#define LOG_E(message) LOG(Log::Error, message)

class Log
{
  public:
    // Possible log levels to filter which log message will be displayed.
    enum LogLevel
    {
        Debug,
        Info,
        Warning,
        Error,
    };

    // Getters and setters.
    static void SetLevel(LogLevel level);
    static LogLevel GetLevel();

    // Gets the stream where messages will be displayed.
    static std::ostream& GetStream();

    // Maps log levels to strings for printing purposes.
    static std::string GetLevelString(LogLevel level);

    // Formats current time.
    static std::string GetTime();

    // Maps log levels to colors for printing purposes.
    static std::string GetLevelColor(LogLevel level);

    // Formats a source file name.
    static std::string GetFilename(const std::string& path);

    // Formats a class name.
    static std::string GetClassName(const std::string& prettyFunction);

    // Formats a string to reset terminal color.
    static std::string GetResetColor();

  private:
    // Current log level.
    static LogLevel level;
};

#endif // LOG_HPP