#include "SpriteAnimator.h"
#include <SDL2/SDL_image.h>
#include <iostream>

std::unordered_map<std::string, SDL_Texture*> SpriteAnimator::textureCache;

SpriteAnimator::SpriteAnimator(SDL_Renderer* renderer, const std::string& texturePath,
                               int frameWidth, int frameHeight, int frameDelay, int rows, int columns)
    : frameWidth(frameWidth), frameHeight(frameHeight), frameDelay(frameDelay),
      rows(rows), columns(columns), currentFrameIndex(0), lastFrameTime(0), currentFrameTime(0) {

    texture = LoadTexture(renderer, texturePath);
    totalFrames = rows * columns;
}

SpriteAnimator::~SpriteAnimator() { }

SDL_Texture* SpriteAnimator::LoadTexture(SDL_Renderer* renderer, const std::string& texturePath) {
    auto it = textureCache.find(texturePath);
    if (it != textureCache.end()) {
        return it->second;
    }

    SDL_Surface* surface = IMG_Load(texturePath.c_str());
    if (!surface) {
        std::cerr << "Unable to load image " << texturePath << " SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!newTexture) {
        std::cerr << "Unable to create texture from surface! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    textureCache[texturePath] = newTexture;
    return newTexture;
}

void SpriteAnimator::Update() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastFrameTime >= frameDelay) {
        currentFrameIndex = (currentFrameIndex + 1) % totalFrames;
        lastFrameTime = currentTime;
    }
}

void SpriteAnimator::Render(SDL_Renderer* renderer, int x, int y, double angle) const {
    SDL_Rect sourceRect = GetCurrentFrameRect();
    SDL_Rect destRect = { x, y, frameWidth, frameHeight };
    SDL_RenderCopyEx(renderer, texture, &sourceRect, &destRect, angle, nullptr, SDL_FLIP_NONE);
}

SDL_Rect SpriteAnimator::GetCurrentFrameRect() const {
    int row = currentFrameIndex / columns;
    int col = currentFrameIndex % columns;
    return { col * frameWidth, row * frameHeight, frameWidth, frameHeight };
}

int SpriteAnimator::GetWidth() const { return frameWidth; }
int SpriteAnimator::GetHeight() const { return frameHeight; }
int SpriteAnimator::GetCurrentFrame() const { return currentFrameIndex; }
SDL_Texture* SpriteAnimator::GetTexture() const { return texture; }

void SpriteAnimator::ClearTextureCache() {
    for (auto& pair : textureCache) {
        SDL_DestroyTexture(pair.second);
    }
    textureCache.clear();
}