#include "Player.h"
#include "SDL2/SDL.h"
#include <iostream>

#include "../shooting/ShotgunWeapon.h"

Player::Player(SDL_Renderer* renderer, const std::string& spriteSheetPath, int frameWidth, int frameHeight,
               int frameDelay, int rows, int columns, int x, int y)
    : GameEntity(renderer, spriteSheetPath, frameWidth, frameHeight, frameDelay, rows, columns, x, y),
      engineFlame(renderer, "assets/sprites/ships/engine_flame.png", 240, 240, frameDelay, 4, 4),
      shooter(renderer, x, y),
      velocityX(0), velocityY(0), maxSpeedX(300), maxSpeedY(300), acceleration(5.0f), deceleration(4.0f) {

    // Change the default weapon to ShotgunWeapon
    weapon = std::make_unique<ShotgunWeapon>("assets/sprites/bullets/bullets/shot_3.png", 10, 10, 45.0f, 20);

    // Set the weapon for the shooter
    shooter.SetWeapon(weapon.get());
}


Player::~Player() {}

void Player::Update() {
    const Uint8* keystate = SDL_GetKeyboardState(nullptr);

    HandleMovement(keystate);
    HandleMouseMovement();

    ClampVelocity();
    ApplyDeceleration();

    posX += velocityX;
    posY += velocityY;

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
    shooter.SetRotation(0.0f);
    shooter.Update();
}

void Player::Render(SDL_Renderer* renderer)  {
    GameEntity::Render(renderer);

    int flameOffsetX = GetWidth() / 2 - engineFlame.GetAnimator().GetWidth() / 2;
    int flameOffsetY = GetHeight();

    engineFlame.Render(renderer, GetPosX() + flameOffsetX, GetPosY() + flameOffsetY * 0.5f, 180.0f);
    shooter.Render(renderer);
}

void Player::HandleMovement(const Uint8* keystate) {
    if (keystate[SDL_SCANCODE_W]) {
        velocityY -= acceleration;
    }
    if (keystate[SDL_SCANCODE_S]) {
        velocityY += acceleration;
    }
    if (keystate[SDL_SCANCODE_A]) {
        velocityX -= acceleration;
    }
    if (keystate[SDL_SCANCODE_D]) {
        velocityX += acceleration;
    }
}

void Player::HandleMouseMovement() {
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        if (mouseX < posX) {
            velocityX -= acceleration;
        } else if (mouseX > posX + GetWidth()) {
            velocityX += acceleration;
        }

        if (mouseY < posY) {
            velocityY -= acceleration;
        } else if (mouseY > posY + GetHeight()) {
            velocityY += acceleration;
        }
    }
}

void Player::ClampVelocity() {
    if (velocityX > maxSpeedX) velocityX = maxSpeedX;
    if (velocityX < -maxSpeedX) velocityX = -maxSpeedX;
    if (velocityY > maxSpeedY) velocityY = maxSpeedY;
    if (velocityY < -maxSpeedY) velocityY = -maxSpeedY;
}

void Player::ApplyDeceleration() {
    if (!SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_W] && !SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_S]) {
        if (std::abs(velocityY) > deceleration) {
            velocityY -= (velocityY > 0 ? deceleration : -deceleration);
        } else {
            velocityY = 0;
        }
    }

    if (!SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_A] && !SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_D]) {
        if (std::abs(velocityX) > deceleration) {
            velocityX -= (velocityX > 0 ? deceleration : -deceleration);
        } else {
            velocityX = 0;
        }
    }
}