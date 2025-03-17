#ifndef GAME_SETTINGS_H
#define GAME_SETTINGS_H

#include <string>
#include "../helpers/IniReader.h"

class GameSettings {
    std::string iniFile;
    int windowWidth;
    int windowHeight;
    bool fullscreen;
    IniReader iniReader;

public:
    GameSettings(const std::string& iniFile);

    bool Load();

    int GetWindowWidth() const;
    int GetWindowHeight() const;
    bool IsFullscreen() const;
};

#endif