#include "Player.h"
#include "SDL2/SDL.h"
#include <iostream>
#include <cmath>

#include "../helpers/Tags.h"
#include "../shooting/ShotgunWeapon.h"

Player::Player(SDL_Renderer* renderer, const std::string& spriteSheetPath, int frameWidth, int frameHeight,
               int frameDelay, int rows, int columns, int x, int y)
    : GameEntity(renderer, spriteSheetPath, frameWidth, frameHeight, frameDelay, rows, columns, x, y),
      engineFlame(renderer),
      shooter(renderer, x, y),
      velocityX(0), velocityY(0), maxSpeedX(600), maxSpeedY(600), acceleration(1000.0f), deceleration(1000.0f) {

    SetTag(Tags::Player);

    weapon = std::make_unique<ShotgunWeapon>("assets/sprites/bullets/bullets/shot_3.png", 10, 10, 45, 250);
    shooter.SetWeapon(weapon.get());
}

Player::~Player() = default;

void Player::Update(float deltaTime) {
    const Uint8* keystate = SDL_GetKeyboardState(nullptr);

    HandleMovement(keystate, deltaTime);
    HandleMouseMovement(deltaTime);

    ClampVelocity();
    ApplyDeceleration(deltaTime);

    posX += velocityX * deltaTime;
    posY += velocityY * deltaTime;

    SDL_Window* window = SDL_GetWindowFromID(1);
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    if (posX < 0) posX = 0;
    if (posX + GetWidth() > windowWidth) posX = windowWidth - GetWidth();
    if (posY < 0) posY = 0;
    if (posY + GetHeight() > windowHeight) posY = windowHeight - GetHeight();

    animator->Update();
    engineFlame.Update();

    shooter.SetPosition(posX + GetWidth() * 0.5f, posY);
    shooter.Update();
}

void Player::Render(SDL_Renderer* renderer)  {
    GameEntity::Render(renderer);

    int flameOffsetX = GetWidth() / 2 - engineFlame.GetAnimator().GetWidth() / 2;
    int flameOffsetY = GetHeight();

    engineFlame.Render(GetPosX() + flameOffsetX, GetPosY() + flameOffsetY * 0.5f, 180.0f);
}

void Player::OnCollisionEnter(GameEntity &other)
{

}

void Player::HandleMovement(const Uint8* keyState, float deltaTime) {
    if (keyState[SDL_SCANCODE_W]) {
        velocityY -= acceleration * deltaTime;
    }
    if (keyState[SDL_SCANCODE_S]) {
        velocityY += acceleration * deltaTime;
    }
    if (keyState[SDL_SCANCODE_A]) {
        velocityX -= acceleration * deltaTime;
    }
    if (keyState[SDL_SCANCODE_D]) {
        velocityX += acceleration * deltaTime;
    }
}

void Player::HandleMouseMovement(float deltaTime) {
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {

        float dirX = mouseX - (posX + GetWidth() / 2);
        float dirY = mouseY - (posY + GetHeight() / 2);

        float distance = sqrt(dirX * dirX + dirY * dirY);
        float threshold = GetWidth() * 0.5f;

        if (distance > threshold) {

            dirX /= distance;
            dirY /= distance;

            velocityX = dirX * acceleration;
            velocityY = dirY * acceleration;
        } else {

            velocityX = 0.0f;
            velocityY = 0.0f;
        }
    }
}

void Player::ClampVelocity() {
    if (velocityX > maxSpeedX) velocityX = maxSpeedX;
    if (velocityX < -maxSpeedX) velocityX = -maxSpeedX;
    if (velocityY > maxSpeedY) velocityY = maxSpeedY;
    if (velocityY < -maxSpeedY) velocityY = -maxSpeedY;
}

void Player::ApplyDeceleration(float deltaTime) {
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);

    if (!keyState[SDL_SCANCODE_W] && !keyState[SDL_SCANCODE_S]) {
        if (std::abs(velocityY) > deceleration * deltaTime) {
            velocityY -= (velocityY > 0 ? deceleration * deltaTime : -deceleration * deltaTime);
        } else {
            velocityY = 0;
        }
    }

    if (!keyState[SDL_SCANCODE_A] && !keyState[SDL_SCANCODE_D]) {

        if (std::abs(velocityX) > deceleration * deltaTime) {
            velocityX -= (velocityX > 0 ? deceleration * deltaTime : -deceleration * deltaTime);
        } else {
            velocityX = 0;
        }
    }
}