#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include "../helpers/INIReader.h"
#include <string>

class GameSettings {
public:
    GameSettings(const std::string& filename);
    bool Load();
    std::string GetTitle() const;
    int GetWindowWidth() const;
    int GetWindowHeight() const;
    bool IsFullscreen() const;

private:
    INIReader reader;
};

#endif
