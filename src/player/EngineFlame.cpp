#include "EngineFlame.h"

EngineFlame::EngineFlame(SDL_Renderer* renderer)
    : animator(renderer, "assets/sprites/ships/engine_flame.png", 240, 240, 100, 4, 4) {
}

EngineFlame::~EngineFlame() = default;

void EngineFlame::Update() {
    animator.Update();
}

void EngineFlame::Render(float x, float y, float angle) const {
    animator.Render(static_cast<int>(x), static_cast<int>(y), angle);
}

SpriteAnimator& EngineFlame::GetAnimator() {
    return animator;
}
