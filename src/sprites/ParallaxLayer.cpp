#include "ParallaxLayer.h"

#include <iostream>
#include <ostream>
#include <SDL2/SDL_image.h>

ParallaxLayer::ParallaxLayer(SDL_Renderer* renderer, const char* filePath, float speedFactor)
    : texture(nullptr), speed(speedFactor), scrollPosition(0.0f), isLoaded(false) {

    SDL_Surface* surface = IMG_Load(filePath);
    if (!surface) {
        std::cerr << "Failed to load texture: " << IMG_GetError() << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);
    isLoaded = true;
}

ParallaxLayer::~ParallaxLayer() {
    if (texture) SDL_DestroyTexture(texture);
}

void ParallaxLayer::Update(float deltaTime) {
    if (!isLoaded) return;

    scrollPosition += speed * deltaTime;
    if (scrollPosition >= textureHeight) scrollPosition -= textureHeight;
    if (scrollPosition < 0) scrollPosition += textureHeight;
}

void ParallaxLayer::Render(SDL_Renderer* renderer) const {

    if (!isLoaded || !texture) return;

    int yOffset = static_cast<int>(scrollPosition);

    SDL_Rect destRect1 = { 0, -yOffset, textureWidth, textureHeight };
    SDL_RenderCopy(renderer, texture, nullptr, &destRect1);

    SDL_Rect destRect2 = { 0, textureHeight - yOffset, textureWidth, textureHeight };
    SDL_RenderCopy(renderer, texture, nullptr, &destRect2);
}
