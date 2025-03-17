#include "INIReader.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

INIReader::INIReader(const std::string& filename) : filename(filename) {}

bool INIReader::Load() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    std::string current_section;

    while (std::getline(file, line)) {
        if (!ParseLine(line, current_section)) {
        }
    }

    file.close();
    return true;
}

bool INIReader::ParseLine(const std::string& line, std::string& current_section) {
    if (line.empty() || line[0] == ';') {
        return true;
    }

    if (line[0] == '[') {
        size_t end_pos = line.find(']');
        if (end_pos != std::string::npos) {
            current_section = line.substr(1, end_pos - 1);
        }
        return true;
    }

    size_t equal_pos = line.find('=');
    if (equal_pos != std::string::npos) {
        std::string key = line.substr(0, equal_pos);
        std::string value = line.substr(equal_pos + 1);

        key.erase(key.find_last_not_of(" \t\r\n") + 1);
        value.erase(value.find_last_not_of(" \t\r\n") + 1);
        data[current_section][key] = value;
    }

    return true;
}

std::string INIReader::GetString(const std::string& section, const std::string& key, const std::string& default_value) const {
    auto section_it = data.find(section);
    if (section_it != data.end()) {
        auto key_it = section_it->second.find(key);
        if (key_it != section_it->second.end()) {
            return key_it->second;
        }
    }
    return default_value;
}

int INIReader::GetInteger(const std::string& section, const std::string& key, int default_value) const {
    std::string value = GetString(section, key, "");
    if (!value.empty()) {
        try {
            return std::stoi(value);
        } catch (...) {
            return default_value;
        }
    }
    return default_value;
}

bool INIReader::GetBoolean(const std::string& section, const std::string& key, bool default_value) const {
    std::string value = GetString(section, key, "");
    std::transform(value.begin(), value.end(), value.begin(), ::tolower);
    if (value == "true" || value == "1") {
        return true;
    }
    if (value == "false" || value == "0") {
        return false;
    }
    return default_value;
}