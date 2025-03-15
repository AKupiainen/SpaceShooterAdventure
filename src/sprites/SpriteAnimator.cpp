#include "SpriteAnimator.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <chrono>

SpriteAnimator::SpriteAnimator(SDL_Renderer* renderer, const std::string& texturePath,
                               int frameWidth, int frameHeight, int frameDelay, int rows, int columns)
    : frameWidth(frameWidth), frameHeight(frameHeight), frameDelay(frameDelay),
      rows(rows), columns(columns), currentFrameIndex(0), lastFrameTime(0), currentFrameTime(0) {

    SDL_Surface* surface = IMG_Load(texturePath.c_str());
    if (!surface) {
        std::cerr << "Unable to load image " << texturePath << " SDL_image Error: " << IMG_GetError() << std::endl;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Unable to create texture from surface! SDL Error: " << SDL_GetError() << std::endl;
    }

    totalFrames = rows * columns;
}

SpriteAnimator::~SpriteAnimator() {

    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void SpriteAnimator::Update() {

    Uint32 currentTime = SDL_GetTicks();

    if (currentTime - lastFrameTime >= frameDelay) {
        currentFrameIndex++;
        if (currentFrameIndex >= totalFrames) {
            currentFrameIndex = 0;
        }

        lastFrameTime = currentTime;
    }
}

SDL_Rect SpriteAnimator::GetCurrentFrameRect() const {

    int row = currentFrameIndex / columns;
    int col = currentFrameIndex % columns;

    SDL_Rect frameRect;
    frameRect.x = col * frameWidth;
    frameRect.y = row * frameHeight;
    frameRect.w = frameWidth;
    frameRect.h = frameHeight;

    return frameRect;
}

void SpriteAnimator::Render(SDL_Renderer* renderer, int x, int y, double angle) {
    SDL_Rect sourceRect = GetCurrentFrameRect();

    int newWidth = frameWidth;
    int newHeight = frameHeight;

    SDL_Rect destRect = { x, y, newWidth, newHeight };

    SDL_RenderCopyEx(renderer, texture, &sourceRect, &destRect, angle, nullptr, SDL_FLIP_NONE);
}

int SpriteAnimator::GetWidth() const {
    return frameWidth;
}

int SpriteAnimator::GetHeight() const {
    return frameHeight;
}

SDL_Texture* SpriteAnimator::GetTexture() const {
    return texture;
}