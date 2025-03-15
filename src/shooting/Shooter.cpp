#include "Shooter.h"
#include "Bullet.h"
#include "../core/Time.h"
#include <iostream>

Shooter::Shooter(SDL_Renderer* renderer, int playerX, int playerY)
    : renderer(renderer), playerX(playerX), playerY(playerY), shootCooldown(0.5f), timeSinceLastShot(0.0f), currentWeapon(nullptr) {
}

Shooter::~Shooter() {
    for (Bullet* bullet : bullets) {
        delete bullet;
    }
    bullets.clear();
}

void Shooter::Shoot(BulletPath* path, int bulletWidth, int bulletHeight, const std::string& texturePath, double angle) {
    if (timeSinceLastShot >= shootCooldown) {
        auto newBullet = new Bullet(renderer, playerX, playerY, path, bulletWidth, bulletHeight, texturePath);
        newBullet->SetRotation(angle);
        bullets.push_back(newBullet);

        timeSinceLastShot = 0.0f;
    }
}

void Shooter::Update() {
    for (auto it = bullets.begin(); it != bullets.end();) {
        Bullet* bullet = *it;
        bullet->Update();

        if (!bullet->IsActive()) {
            delete bullet;
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }

    timeSinceLastShot += Time::GetDeltaTime();

    if (currentWeapon) {
        currentWeapon->Shoot(*this);
    }
}

void Shooter::Render(SDL_Renderer* renderer) const {
    for (Bullet* bullet : bullets) {
        bullet->Render(renderer);
    }
}

void Shooter::SetPosition(int x, int y) {
    playerX = x;
    playerY = y;
}

void Shooter::SetWeapon(std::unique_ptr<Weapon> weapon) {
    currentWeapon = std::move(weapon);
}

float Shooter::GetTimeSinceLastShot() const {
    return timeSinceLastShot;
}