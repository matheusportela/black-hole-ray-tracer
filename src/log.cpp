#include "log.hpp"

Log::LogLevel Log::level = Log::Info;

void Log::SetLevel(LogLevel level)
{
    Log::level = level;
}

Log::LogLevel Log::GetLevel()
{
    return Log::level;
}

std::ostream& Log::GetStream()
{
    return std::cerr;
};

std::string Log::GetLevelString(LogLevel level)
{
    switch (level)
    {
        case Debug:
            return "D";
        case Info:
            return "I";
        case Warning:
            return "W";
        case Error:
            return "E";
        default:
            std::cerr << "ERROR [Log] Log level \"" << level << "\" undefined."
                  << std::endl;
            exit(1);
    }
}

std::string Log::GetTime() {
    std::time_t t = std::time(nullptr);
    char mbstr[100];
    if (std::strftime(mbstr, sizeof(mbstr), "%H:%M:%S", std::localtime(&t))) {
        return std::string(mbstr);
    }
    return "";
}

std::string Log::GetLevelColor(LogLevel level)
{
    // Reference: https://stackoverflow.com/a/2616912
    switch (level)
    {
        case Debug:
            return "\e[1;35m"; // purple
        case Info:
            return "\e[1;37m"; // white
        case Warning:
            return "\e[1;33m"; // yellow
        case Error:
            return "\e[1;31m"; // red
    }

    std::cerr << "ERROR [Log] Log level \"" << level << "\" undefined."
              << std::endl;
    exit(1);
}

std::string Log::GetFilename(const std::string& path) {
    size_t begin = path.rfind("/") + 1;
    size_t end = path.length();
    return path.substr(begin, end);
}

std::string Log::GetClassName(const std::string& prettyFunction) {
    // Reference: https://stackoverflow.com/a/15775519
    size_t colons = prettyFunction.find("::");
    if (colons == std::string::npos)
        return "::";
    size_t begin = prettyFunction.substr(0, colons).rfind(" ") + 1;
    size_t end = colons - begin;
    return prettyFunction.substr(begin, end);
}

std::string Log::GetResetColor()
{
    return "\e[0;0m";
}