#ifndef SPRITEANIMATOR_H
#define SPRITEANIMATOR_H

#include <SDL2/SDL.h>
#include <string>

class SpriteAnimator {
public:
    SpriteAnimator(SDL_Renderer* renderer, const std::string& texturePath,
                   int frameWidth, int frameHeight, int frameDelay, int rows, int columns);
    ~SpriteAnimator();

    void Update();
    void Render(SDL_Renderer* renderer, int x, int y, double angle);

    SDL_Rect GetCurrentFrameRect() const;
    SDL_Texture* GetTexture() const;

    int GetWidth() const;
    int GetHeight() const;
    int GetCurrentFrame() const;

private:
    SDL_Texture* texture;
    int frameWidth;
    int frameHeight;
    int frameDelay;
    int totalFrames;
    int rows;
    int columns;
    int currentFrameIndex;
    Uint32 lastFrameTime;
    int currentFrameTime;
};

#endif
