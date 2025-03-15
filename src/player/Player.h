#pragma once

#include "../core/GameEntity.h"
#include "EngineFlame.h"
#include "../shooting/Shooter.h"
#include <SDL2/SDL.h>

class Player : public GameEntity {
public:
    Player(SDL_Renderer* renderer, const std::string& spriteSheetPath, int frameWidth, int frameHeight,
           int frameDelay, int rows, int columns, int x, int y);
    ~Player();

    void Update() override;
    void Render(SDL_Renderer* renderer) override;

private:
    void HandleMovement(const Uint8* keystate);
    void HandleMouseMovement();
    void ClampVelocity();
    void ApplyDeceleration();

    EngineFlame engineFlame;
    Shooter shooter;

    float velocityX, velocityY;
    const float maxSpeedX, maxSpeedY;
    const float acceleration, deceleration;
};
