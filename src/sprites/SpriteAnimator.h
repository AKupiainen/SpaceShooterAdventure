#ifndef SPRITEANIMATOR_H
#define SPRITEANIMATOR_H

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

class SpriteAnimator {
public:
    SpriteAnimator(SDL_Renderer* renderer, const std::string& texturePath,
                   int frameWidth, int frameHeight, int frameDelay, int rows, int columns);
    ~SpriteAnimator();

    void Update();
    void Render(int x, int y, double angle) const;

    [[nodiscard]] SDL_Rect GetCurrentFrameRect() const;
    [[nodiscard]] SDL_Texture* GetTexture() const;

    [[nodiscard]] int GetWidth() const;
    [[nodiscard]] int GetHeight() const;
    [[nodiscard]] int GetCurrentFrame() const;

    static void ClearTextureCache();

private:
    SDL_Renderer* renderer;
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

    static std::unordered_map<std::string, SDL_Texture*> textureCache;
    static SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& texturePath);
};

#endif
