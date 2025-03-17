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
    explicit GameSettings(std::string  iniFile);

    bool Load();

    [[nodiscard]] int GetWindowWidth() const;
    [[nodiscard]] int GetWindowHeight() const;
    [[nodiscard]] bool IsFullscreen() const;
};

#endif