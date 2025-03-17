#ifndef INI_READER_H
#define INI_READER_H

#include <string>
#include <unordered_map>

class IniReader {
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data;

public:
    bool loadFile(const std::string& filename);

    std::string getString(const std::string& section, const std::string& key,
                          const std::string& defaultValue = "") const;

    int getInt(const std::string& section, const std::string& key,
               int defaultValue = 0) const;

    float getFloat(const std::string& section, const std::string& key,
                   float defaultValue = 0.0f) const;

    bool getBool(const std::string& section, const std::string& key,
                 bool defaultValue = false) const;

private:
    static std::string trim(const std::string& str);
};

#endif