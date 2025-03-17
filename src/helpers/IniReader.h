#ifndef INI_READER_H
#define INI_READER_H

#include <string>
#include <unordered_map>

class IniReader {
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data;

public:
    bool loadFile(const std::string& filename);

    [[nodiscard]] std::string getString(const std::string& section, const std::string& key,
                          const std::string& defaultValue = "") const;

    [[nodiscard]] int getInt(const std::string& section, const std::string& key,
               int defaultValue = 0) const;

    [[nodiscard]] float getFloat(const std::string& section, const std::string& key,
                   float defaultValue = 0.0f) const;

    [[nodiscard]] bool getBool(const std::string& section, const std::string& key,
                 bool defaultValue = false) const;

private:
    static std::string trim(const std::string& str);
};

#endif