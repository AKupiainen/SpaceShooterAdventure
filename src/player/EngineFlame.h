#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "../sprites/SpriteAnimator.h"

class EngineFlame {
public:
    EngineFlame(SDL_Renderer* renderer, const std::string& spriteSheetPath, int frameWidth, int frameHeight,
                int frameDelay, int rows, int columns);
    ~EngineFlame();

    void Update();
    void Render(SDL_Renderer* renderer, float x, float y, float angle) const;

    SpriteAnimator& GetAnimator();

private:
    SpriteAnimator animator;
};
