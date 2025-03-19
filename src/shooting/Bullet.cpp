#include "Bullet.h"
#include "BulletPath.h"
#include <iostream>
#include <SDL_render.h>

Bullet::Bullet(SDL_Renderer* renderer, int x, int y, BulletPath* path, int width, int height, const std::string& texturePath)
    : GameEntity(renderer, texturePath, width, height, 100, 1, 1, x, y), path(path) {
}

Bullet::~Bullet() {
    delete path;
}

void Bullet::Update() {

    if (path) {
        path->Update(posX, posY, rotationAngle);
    }

    SDL_Window* window = SDL_GetWindowFromID(1);
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    if (posX < 0 || posX > windowWidth || posY < 0 || posY > windowHeight) {
        active = false;
    }
}

void Bullet::Render(SDL_Renderer* renderer) {

    if (active && GetTexture()) {
        SDL_Rect renderRect = { static_cast<int>(posX), static_cast<int>(posY), GetWidth(), GetHeight() };
        SDL_Point center = { GetWidth() / 2, GetHeight() / 2 };

        SDL_RenderCopyEx(renderer, GetTexture(), nullptr, &renderRect, rotationAngle, &center, SDL_FLIP_NONE);
    }
}

void Bullet::OnCollisionEnter(GameEntity &other)
{

}