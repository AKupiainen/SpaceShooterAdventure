#include "Shooter.h"
#include "Bullet.h"
#include "../core/Time.h"
#include <iostream>
#include "../core/DependencyInjection.h"
#include "../core/CollisionManager.h"

Shooter::Shooter(SDL_Renderer* renderer, int x, int y)
    : renderer(renderer), playerX(x), playerY(y),
      shootCooldown(0.5f), timeSinceLastShot(0.0f), currentWeapon(nullptr) {
}

Shooter::~Shooter() {
    for (Bullet* bullet : bullets) {
        delete bullet;
    }
    bullets.clear();
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

    if (currentWeapon && timeSinceLastShot >= shootCooldown) {
        currentWeapon->Fire(*this);
        timeSinceLastShot = 0.0f;
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

void Shooter::AddBullet(Bullet* bullet) {
    bullets.push_back(bullet);
    std::shared_ptr<CollisionManager> collisionManager = DependencyInjection::Resolve<CollisionManager>();
    collisionManager->AddEntity(bullet);
}