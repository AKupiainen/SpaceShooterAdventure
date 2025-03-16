#include "DebugLog.h"

void DebugLog::Log(const std::string& message) {
    std::cout << "[LOG] " << message << std::endl;
}

void DebugLog::LogError(const std::string& message) {
    std::cerr << "[ERROR] " << message << std::endl;
}

void DebugLog::LogWarning(const std::string& message) {
    std::cout << "[WARNING] " << message << std::endl;
}