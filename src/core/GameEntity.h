#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <SDL2/SDL.h>
#include <string>
#include "../sprites/SpriteAnimator.h"

class CollisionBox {
public:
    CollisionBox(int x, int y, int w, int h) : x(x), y(y), width(w), height(h) {}
    void SetPosition(int newX, int newY) { x = newX; y = newY; }
    SDL_Rect GetRect() const { return { x, y, width, height }; }
    bool CheckCollision(const CollisionBox& other) const {
        SDL_Rect a = GetRect();
        SDL_Rect b = other.GetRect();
        return SDL_HasIntersection(&a, &b);
    }

private:
    int x, y, width, height;
};

class GameEntity {
public:
    GameEntity(SDL_Renderer* renderer, const std::string& spriteSheetPath, int frameWidth,
               int frameHeight, int frameDelay, int rows, int columns, int x, int y);
    virtual ~GameEntity();

    virtual void Update() = 0;
    virtual void Render(SDL_Renderer* renderer);

    void IncrementRotation(double angleIncrement);
    void UpdateCollisionBox();
    bool CheckCollision(const GameEntity& other) const;

    int GetPosX() const { return static_cast<int>(posX); }
    int GetPosY() const { return static_cast<int>(posY); }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

    SDL_Texture* GetTexture() const { return animator->GetTexture(); }

    void SetRotation(int angleIncrement) { rotationAngle = angleIncrement; }

    CollisionBox& GetCollisionBox() { return collisionBox; }

    virtual void OnCollisionEnter(GameEntity& other);

protected:
    double posX, posY;
    double velocityX, velocityY;
    double maxSpeedX, maxSpeedY;
    float acceleration, deceleration;
    int width, height;
    double rotationAngle;

    SpriteAnimator* animator;
    CollisionBox collisionBox;
};

#endif
