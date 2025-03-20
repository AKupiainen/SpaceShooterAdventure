#include "GameSettings.h"
#include <iostream>

GameSettings::GameSettings(std::string  iniFile)
    : iniFile(std::move(iniFile)), windowWidth(1920), windowHeight(1080), fullscreen(false) {}

bool GameSettings::Load() {
    if (!iniReader.LoadFile(iniFile)) {
        std::cerr << "Failed to load INI file: " << iniFile << std::endl;
        return false;
    }

    windowWidth = iniReader.GetInt("Graphics", "ScreenWidth", 1920);
    windowHeight = iniReader.GetInt("Graphics", "ScreenHeight", 1080);
    fullscreen = iniReader.GetBool("Graphics", "Fullscreen", false);

    return true;
}

int GameSettings::GetWindowWidth() const {
    return windowWidth;
}

int GameSettings::GetWindowHeight() const {
    return windowHeight;
}

bool GameSettings::IsFullscreen() const {
    return fullscreen;
}