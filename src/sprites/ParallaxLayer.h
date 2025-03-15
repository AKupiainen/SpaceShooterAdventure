#ifndef PARALLAX_LAYER_H
#define PARALLAX_LAYER_H
#include <SDL2/SDL.h>

class ParallaxLayer {

    SDL_Texture* texture;
    int textureWidth, textureHeight;
    float speed;
    float scrollPosition;
    bool isLoaded;

public:
    ParallaxLayer(SDL_Renderer* renderer, const char* filePath, float speedFactor);
    ~ParallaxLayer();

    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer) const;
};

#endif