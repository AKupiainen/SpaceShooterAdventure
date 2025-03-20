#ifndef INI_READER_H
#define INI_READER_H

#include <string>
#include <unordered_map>
#include <vector>

class IniReader {
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data;

public:
    bool LoadFile(const std::string& filename);

    [[nodiscard]] std::string GetString(const std::string& section, const std::string& key,
                          const std::string& defaultValue = "") const;

    [[nodiscard]] int GetInt(const std::string& section, const std::string& key,
               int defaultValue = 0) const;

    [[nodiscard]] float GetFloat(const std::string& section, const std::string& key,
                   float defaultValue = 0.0f) const;

    [[nodiscard]] bool GetBool(const std::string& section, const std::string& key,
                 bool defaultValue = false) const;

    [[nodiscard]] std::vector<std::string> GetArray(const std::string& section, const std::string& key) const;

private:
    static std::string Trim(const std::string& str);
};

#endif
