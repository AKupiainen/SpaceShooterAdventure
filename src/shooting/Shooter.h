#pragma once

#include <SDL2/SDL.h>
#include "Weapon.h"

class Bullet;
class BulletPath;
class Weapon;

class Shooter {
public:
    Shooter(SDL_Renderer* renderer, int x, int y);
    ~Shooter();

    void Update();
    void SetPosition(double x, double y);

    void SetWeapon(Weapon* weaponPtr) {
        currentWeapon = weaponPtr;
    }

    [[nodiscard]] float GetShootCooldown() const { return shootCooldown; }
    void SetShootCooldown(float cooldown) { shootCooldown = cooldown; }

    [[nodiscard]] double GetX() const { return playerX; }
    [[nodiscard]] double GetY() const { return playerY; }

    [[nodiscard]] SDL_Renderer* GetRenderer() const { return renderer; }

    [[nodiscard]] float GetRotation() const { return rotation; }
    void SetRotation(float angle) { rotation = angle; }

private:
    Weapon* currentWeapon;
    SDL_Renderer* renderer;
    double playerX, playerY;
    float shootCooldown;
    float timeSinceLastShot;
    float rotation;
};