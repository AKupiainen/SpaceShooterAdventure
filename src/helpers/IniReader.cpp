#include "IniReader.h"

#include <fstream>
#include <iostream>

bool IniReader::loadFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    data.clear();
    std::string currentSection = "";

    std::string line;
    while (std::getline(file, line)) {

        line = trim(line);

        if (line.empty() || line[0] == ';' || line[0] == '#')
            continue;

        if (line[0] == '[' && line[line.length() - 1] == ']') {
            currentSection = line.substr(1, line.length() - 2);
            continue;
        }

        size_t delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos) {
            std::string key = trim(line.substr(0, delimiterPos));
            std::string value = trim(line.substr(delimiterPos + 1));
            data[currentSection][key] = value;
        }
    }

    file.close();
    return true;
}

std::string IniReader::getString(const std::string& section, const std::string& key,
                      const std::string& defaultValue) const {
    if (data.count(section) && data.at(section).count(key)) {
        return data.at(section).at(key);
    }
    return defaultValue;
}

int IniReader::getInt(const std::string& section, const std::string& key,
           int defaultValue) const {
    try {
        std::string value = getString(section, key, "");
        if (!value.empty()) {
            return std::stoi(value);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error converting to int: " << e.what() << std::endl;
    }
    return defaultValue;
}

float IniReader::getFloat(const std::string& section, const std::string& key,
               float defaultValue) const {
    try {
        std::string value = getString(section, key, "");
        if (!value.empty()) {
            return std::stof(value);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error converting to float: " << e.what() << std::endl;
    }
    return defaultValue;
}

bool IniReader::getBool(const std::string& section, const std::string& key,
             bool defaultValue) const {
    std::string value = getString(section, key, "");
    if (!value.empty()) {

        std::string lowerValue = value;
        for (char& c : lowerValue) {
            c = std::tolower(c);
        }

        if (lowerValue == "true" || lowerValue == "yes" || lowerValue == "1")
            return true;
        if (lowerValue == "false" || lowerValue == "no" || lowerValue == "0")
            return false;
    }
    return defaultValue;
}

std::string IniReader::trim(const std::string& str) {
    const std::string whitespace = " \t\r\n";
    size_t start = str.find_first_not_of(whitespace);
    if (start == std::string::npos) {
        return "";
    }
    size_t end = str.find_last_not_of(whitespace);
    return str.substr(start, end - start + 1);
}