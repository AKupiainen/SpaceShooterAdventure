#pragma once

#include "../core/GameEntity.h"
#include "../player//EngineFlame.h"
#include "../shooting/Shooter.h"
#include <SDL2/SDL.h>

class Enemy : public GameEntity {
public:
    Enemy(SDL_Renderer* renderer, const std::string& spriteSheetPath, int frameWidth, int frameHeight,
          int frameDelay, int rows, int columns, int x, int y, float speedX, float speedY);
    ~Enemy() override;

    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer) override;
    void OnCollisionEnter(GameEntity& other) override;

private:

    EngineFlame engineFlame;
    Shooter shooter;

    float movementSpeedX;
    float movementSpeedY;
};