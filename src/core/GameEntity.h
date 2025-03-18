#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <SDL2/SDL.h>
#include <string>
#include "../sprites/SpriteAnimator.h"

class CollisionBox {
public:
    CollisionBox(int x, int y, int w, int h) : x(x), y(y), width(w), height(h) {}
    void SetPosition(int newX, int newY) { x = newX; y = newY; }
    [[nodiscard]] SDL_Rect GetRect() const { return { x, y, width, height }; }
    [[nodiscard]] bool CheckCollision(const CollisionBox& other) const {
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

    virtual void Update(float deltaTime) = 0;
    virtual void Render(SDL_Renderer* renderer);

    void IncrementRotation(double angleIncrement);
    void UpdateCollisionBox();

    [[nodiscard]] bool CheckCollision(const GameEntity& other) const;
    [[nodiscard]] int GetPosX() const { return static_cast<int>(posX); }
    [[nodiscard]] int GetPosY() const { return static_cast<int>(posY); }
    [[nodiscard]] int GetWidth() const { return width; }
    [[nodiscard]] int GetHeight() const { return height; }

    [[nodiscard]] SDL_Texture* GetTexture() const { return animator->GetTexture(); }

    void SetRotation(int angleIncrement) { rotationAngle = angleIncrement; }

    CollisionBox& GetCollisionBox() { return collisionBox; }

    void SetTag(const std::string& newTag) { tag = newTag; }
    [[nodiscard]] const std::string& GetTag() const { return tag; }

    [[nodiscard]] bool IsActive() const { return active; }

    virtual void OnCollisionEnter(GameEntity& other);

protected:
    double posX, posY;
    double velocityX, velocityY;
    double maxSpeedX, maxSpeedY;
    float acceleration, deceleration;
    int width, height;
    double rotationAngle;
    bool active = true;

    SpriteAnimator* animator;
    CollisionBox collisionBox;

    std::string tag;
};

#endif