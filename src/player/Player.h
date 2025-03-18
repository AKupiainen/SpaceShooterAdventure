#pragma once

#include "../core/GameEntity.h"
#include "EngineFlame.h"
#include "../shooting/Shooter.h"
#include "../shooting/Weapon.h"
#include <SDL2/SDL.h>

class Player : public GameEntity {
public:
    Player(SDL_Renderer* renderer, const std::string& spriteSheetPath, int frameWidth, int frameHeight,
           int frameDelay, int rows, int columns, int x, int y);
    ~Player() override;

    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;
    void OnCollisionEnter(GameEntity& other) override;

private:
    void HandleMovement(const Uint8* keyState);
    void HandleMouseMovement();
    void ClampVelocity();
    void ApplyDeceleration();

    EngineFlame engineFlame;
    Shooter shooter;
    std::unique_ptr<Weapon> weapon;

    float velocityX, velocityY;
    const float maxSpeedX, maxSpeedY;
    const float acceleration, deceleration;
};