#include "GameSettings.h"
#include <iostream>

GameSettings::GameSettings(std::string  iniFile)
    : iniFile(std::move(iniFile)), windowWidth(1920), windowHeight(1080), fullscreen(false) {}

bool GameSettings::Load() {
    if (!iniReader.loadFile(iniFile)) {
        std::cerr << "Failed to load INI file: " << iniFile << std::endl;
        return false;
    }

    windowWidth = iniReader.getInt("Graphics", "ScreenWidth", 1920);
    windowHeight = iniReader.getInt("Graphics", "ScreenHeight", 1080);
    fullscreen = iniReader.getBool("Graphics", "Fullscreen", false);

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