#ifndef PLAYER_H
#define PLAYER_H

#include <SDL_render.h>

#include "../core/GameEntity.h"
#include "../sprites/SpriteAnimator.h"
#include "../bullets/Shooter.h"

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
    SpriteAnimator engineFlame;
    Shooter shooter;
};

#endif