#ifndef DEBUGLOG_H
#define DEBUGLOG_H

#include <iostream>

class DebugLog {
public:
    static void Log(const std::string& message);
    static void LogError(const std::string& message);
    static void LogWarning(const std::string& message);
};

#endif
