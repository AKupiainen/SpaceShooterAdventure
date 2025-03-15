#ifndef PLAYER_H
#define PLAYER_H

#include "GameEntity.h"
#include "SpriteAnimator.h"
#include "Shooter.h"

class Player : public GameEntity {
public:
    Player(SDL_Renderer* renderer, const std::string& spriteSheetPath, int frameWidth, int frameHeight,
           int frameDelay, int rows, int columns, int x, int y);
    ~Player();

    void Update() override;
    void Render(SDL_Renderer* renderer) override;

private:
    float maxSpeedX, maxSpeedY;
    float acceleration, deceleration;
    SpriteAnimator engineFlame;  // SpriteAnimator for engine flame
    Shooter shooter;  // Shooter for handling bullet firing
};

#endif
