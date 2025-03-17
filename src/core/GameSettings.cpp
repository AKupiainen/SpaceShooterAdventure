#include "GameSettings.h"

GameSettings::GameSettings(const std::string& filename) : reader(filename) {}

bool GameSettings::Load() {
    return reader.Load();
}

std::string GameSettings::GetTitle() const {
    return reader.GetString("Game", "Title", "Default Title");
}

int GameSettings::GetWindowWidth() const {
    return reader.GetInteger("Graphics", "Width", 800);
}

int GameSettings::GetWindowHeight() const {
    return reader.GetInteger("Graphics", "Height", 600);
}

bool GameSettings::IsFullscreen() const {
    return reader.GetBoolean("Graphics", "Fullscreen", false);
}
