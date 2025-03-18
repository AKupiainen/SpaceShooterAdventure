#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include "Weapon.h"

class Bullet;
class Weapon;
class GameWorld;

class Shooter {
public:
    Shooter(SDL_Renderer* renderer, int x, int y);
    ~Shooter();

    void Update();
    void SetPosition(double x, double y);

    void SetWeapon(Weapon* weaponPtr);
    void SetShootCooldown(float cooldown);
    void AddBullet(std::unique_ptr<Bullet> bullet) const;

    double GetX() const { return playerX; }
    double GetY() const { return playerY; }

    SDL_Renderer* GetRenderer() const { return renderer; }

    void SetRotation(float angle) { rotation = angle; }
    float GetRotation() const { return rotation; }

private:
    Weapon* currentWeapon = nullptr;
    SDL_Renderer* renderer = nullptr;
    double playerX = 0.0, playerY = 0.0;
    float shootCooldown = 0.5f;
    float timeSinceLastShot = 0.0f;
    float rotation = 0.0f;
    std::shared_ptr<GameWorld> gameWorld;
};