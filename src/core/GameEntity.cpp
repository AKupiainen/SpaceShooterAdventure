#include "GameEntity.h"
#include <iostream>

GameEntity::GameEntity(SDL_Renderer* renderer, const std::string& spriteSheetPath, int frameWidth,
                       int frameHeight, int frameDelay, int rows, int columns, int x, int y)
    : posX(x), posY(y), velocityX(0), velocityY(0), maxSpeedX(300), maxSpeedY(300), acceleration(5.0f),
      deceleration(0.1f), width(frameWidth), height(frameHeight), rotationAngle(0.0),
      collisionBox(x, y, frameWidth, frameHeight)
{
    animator = new SpriteAnimator(renderer, spriteSheetPath, frameWidth, frameHeight, frameDelay, rows, columns);
}

GameEntity::~GameEntity() {
    delete animator;
}

void GameEntity::Render(SDL_Renderer* renderer) {
    animator->Render(renderer, static_cast<int>(posX), static_cast<int>(posY), rotationAngle);
}

void GameEntity::IncrementRotation(double angleIncrement) {
    rotationAngle += angleIncrement;

    if (rotationAngle >= 360.0) {
        rotationAngle -= 360.0;
    }
    if (rotationAngle < 0.0) {
        rotationAngle += 360.0;
    }
}

bool GameEntity::CheckCollision(const GameEntity& other) const {
    return collisionBox.CheckCollision(other.collisionBox);
}

void GameEntity::UpdateCollisionBox() {
    collisionBox.SetPosition(static_cast<int>(posX), static_cast<int>(posY));
}