#include "Enemy.h"
#include <iostream>
#include "../helpers/Tags.h"

Enemy::Enemy(SDL_Renderer* renderer, const std::string& spriteSheetPath, int frameWidth, int frameHeight,
             int frameDelay, int rows, int columns, int x, int y, float speedX, float speedY)
    : GameEntity(renderer, spriteSheetPath, frameWidth, frameHeight, frameDelay, rows, columns, x, y),
      engineFlame(renderer),
      movementSpeedX(speedX), movementSpeedY(speedY) {

    SetTag(Tags::Enemy);
}

Enemy::~Enemy() = default;

void Enemy::Update(float deltaTime) {

    posX += movementSpeedX * deltaTime;
    posY += movementSpeedY * deltaTime;

    animator->Update();
    engineFlame.Update();
}

void Enemy::Render(SDL_Renderer* renderer) {

    GameEntity::Render(renderer);

    int flameOffsetX = GetWidth() / 2 - engineFlame.GetAnimator().GetWidth() / 2;
    int flameOffsetY = GetHeight();

    engineFlame.Render(GetPosX() + flameOffsetX, GetPosY() + flameOffsetY * 0.5f, 0.0f);
}

void Enemy::OnCollisionEnter(GameEntity& other)
{

}