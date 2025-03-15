#include "Player.h"
#include "SDL2/SDL.h"
#include <iostream>
#include "StraightBulletPath.h"

Player::Player(SDL_Renderer* renderer, const std::string& spriteSheetPath, int frameWidth, int frameHeight,
               int frameDelay, int rows, int columns, int x, int y)
    : GameEntity(renderer, spriteSheetPath, frameWidth, frameHeight, frameDelay, rows, columns, x, y),
      engineFlame(renderer, "assets/sprites/ships/engine_flame.png", 240, 240, frameDelay, 4, 4),
      shooter(renderer, x, y) // Initialize the shooter with renderer, player position
{
    maxSpeedX = 300;
    maxSpeedY = 300;
    acceleration = 5.0f;
    deceleration = 4.0f;
}

Player::~Player() {}

void Player::Update() {
    const Uint8* keystate = SDL_GetKeyboardState(nullptr);

    // Movement logic
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

    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        // Calculate movement based on mouse position
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

    if (!keystate[SDL_SCANCODE_W] && !keystate[SDL_SCANCODE_S]) {
        if (std::abs(velocityY) > deceleration) {
            velocityY -= (velocityY > 0 ? deceleration : -deceleration);
        } else {
            velocityY = 0;
        }
    }

    if (!keystate[SDL_SCANCODE_A] && !keystate[SDL_SCANCODE_D]) {
        if (std::abs(velocityX) > deceleration) {
            velocityX -= (velocityX > 0 ? deceleration : -deceleration);
        } else {
            velocityX = 0;
        }
    }

    if (velocityX > maxSpeedX) velocityX = maxSpeedX;
    if (velocityX < -maxSpeedX) velocityX = -maxSpeedX;
    if (velocityY > maxSpeedY) velocityY = maxSpeedY;
    if (velocityY < -maxSpeedY) velocityY = -maxSpeedY;

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

    StraightBulletPath* straightPath = new StraightBulletPath(10, 10);
    shooter.SetPosition(posX + GetWidth() * 0.5f, posY);
    shooter.Shoot(straightPath, 10, 20, "assets/sprites/bullets/bullets/shot_3.png", 270);  // Example: 10x20 bullet size
    shooter.Update();
}

void Player::Render(SDL_Renderer* renderer) {

    GameEntity::Render(renderer);

    int flameOffsetX = GetWidth() / 2 - engineFlame.GetWidth() / 2;
    int flameOffsetY = GetHeight();

    engineFlame.Render(renderer, GetPosX() + flameOffsetX, GetPosY() + flameOffsetY * 0.5f, 180.0f); // The flame facing downwards
    shooter.Render(renderer);
}