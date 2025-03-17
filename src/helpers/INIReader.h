#ifndef INIREADER_H
#define INIREADER_H

#include <string>
#include <unordered_map>

class INIReader {
public:
    INIReader(const std::string& filename);
    bool Load();
    std::string GetString(const std::string& section, const std::string& key, const std::string& default_value = "") const;
    int GetInteger(const std::string& section, const std::string& key, int default_value = 0) const;
    bool GetBoolean(const std::string& section, const std::string& key, bool default_value = false) const;

private:
    std::string filename;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data;

    bool ParseLine(const std::string& line, std::string& current_section);
};

#endif