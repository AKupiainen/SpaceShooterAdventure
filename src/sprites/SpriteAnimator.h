#ifndef SPRITEANIMATOR_H
#define SPRITEANIMATOR_H

#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include <memory>

class SpriteAnimator {
public:
    SpriteAnimator(SDL_Renderer* renderer, const std::string& texturePath,
                   int frameWidth, int frameHeight, int frameDelay, int rows, int columns);
    ~SpriteAnimator();

    void Update();
    void Render(int x, int y, double angle) const;

    int GetWidth() const;
    int GetHeight() const;
    int GetCurrentFrame() const;
    SDL_Texture* GetTexture() const;

    static void ClearTextureCache();

private:
    SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& texturePath);
    SDL_Rect GetCurrentFrameRect() const;

    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int frameWidth;
    int frameHeight;
    int frameDelay;
    int rows;
    int columns;
    int totalFrames;
    int currentFrameIndex;
    Uint32 lastFrameTime;
    Uint32 currentFrameTime;

    static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> textureCache;
};

#endif
