#pragma once

#include <memory>
#include <string>
#include "SDL2/SDL.h"
#include "../core/GameEntity.h"
#include "../player/EngineFlame.h"
#include "../shooting/Shooter.h"
#include "../shooting/Weapon.h"

class Player : public GameEntity {
public:
    Player(SDL_Renderer* renderer, const std::string& spriteSheetPath, int frameWidth, int frameHeight,
           int frameDelay, int rows, int columns, int x, int y);
    ~Player() override;

    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;
    void OnCollisionEnter(GameEntity& other) override;

private:
    void HandleMovement(const Uint8* keyState, float deltaTime);
    void HandleMouseMovement(float deltaTime);
    void ClampVelocity();
    void ApplyDeceleration(float deltaTime);

    EngineFlame engineFlame;
    Shooter shooter;
    std::unique_ptr<Weapon> weapon;

    float velocityX;
    float velocityY;
    float maxSpeedX;
    float maxSpeedY;
    float acceleration;
    float deceleration;
};