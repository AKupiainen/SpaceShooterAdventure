#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <SDL2/SDL.h>
#include <string>
#include "SpriteAnimator.h"

class GameEntity {
public:
    GameEntity(SDL_Renderer* renderer, const std::string& spriteSheetPath, int frameWidth,
               int frameHeight, int frameDelay, int rows, int columns, int x, int y);
    virtual ~GameEntity();

    virtual void Update() = 0;
    virtual void Render(SDL_Renderer* renderer);

    void IncrementRotation(double angleIncrement);

    int GetPosX() const { return static_cast<int>(posX); }
    int GetPosY() const { return static_cast<int>(posY); }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    SDL_Texture* GetTexture() const { return animator->GetTexture(); }

    void SetRotation(int angleIncrement) { rotationAngle = angleIncrement; }

protected:
    double posX, posY;
    double velocityX, velocityY;
    double maxSpeedX, maxSpeedY;
    float acceleration, deceleration;
    int width, height;
    double rotationAngle;

    SpriteAnimator* animator;
};

#endif
