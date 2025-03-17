#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "../sprites/SpriteAnimator.h"

class EngineFlame {
public:
    EngineFlame(SDL_Renderer* renderer);
    ~EngineFlame();

    void Update();
    void Render(float x, float y, float angle) const;

    SpriteAnimator& GetAnimator();

private:
    SpriteAnimator animator;
};
