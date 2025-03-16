#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Weapon.h"

class Bullet;
class BulletPath;
class Weapon;
class CollisionManager;

class Shooter {
public:
    Shooter(SDL_Renderer* renderer, int x, int y);
    ~Shooter();

    void Update();
    void Render(SDL_Renderer* renderer) const;
    void SetPosition(int x, int y);

    void SetWeapon(Weapon* weaponPtr) {
        currentWeapon = weaponPtr;
    }

    float GetShootCooldown() const { return shootCooldown; }
    void SetShootCooldown(float cooldown) { shootCooldown = cooldown; }

    void AddBullet(Bullet* bullet);

    int GetX() const { return playerX; }
    int GetY() const { return playerY; }

    SDL_Renderer* GetRenderer() const { return renderer; }

    float GetRotation() const { return rotation; }
    void SetRotation(float angle) { rotation = angle; }

private:
    Weapon* currentWeapon;
    SDL_Renderer* renderer;
    int playerX, playerY;
    float shootCooldown;
    float timeSinceLastShot;
    float rotation;
    std::vector<Bullet*> bullets;

    std::shared_ptr<CollisionManager> collisionManager;
};