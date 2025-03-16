#include "EngineFlame.h"
#include <iostream>

EngineFlame::EngineFlame(SDL_Renderer* renderer, const std::string& spriteSheetPath, int frameWidth, int frameHeight,
                         int frameDelay, int rows, int columns)
    : animator(renderer, spriteSheetPath, frameWidth, frameHeight, frameDelay, rows, columns) {
}

EngineFlame::~EngineFlame() {}

void EngineFlame::Update() {
    animator.Update();
}

void EngineFlame::Render(SDL_Renderer* renderer, float x, float y, float angle) {
    animator.Render(renderer, static_cast<int>(x), static_cast<int>(y), angle);
}

SpriteAnimator& EngineFlame::GetAnimator() {
    return animator;
}