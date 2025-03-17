#include "Shooter.h"
#include "Bullet.h"
#include "../core/Time.h"
#include <iostream>
#include "../core/DependencyInjection.h"
#include "../core/CollisionManager.h"

Shooter::Shooter(SDL_Renderer* renderer, int x, int y)
    : currentWeapon(nullptr), renderer(renderer), playerX(x),
      playerY(y), shootCooldown(0.5f), timeSinceLastShot(0.0f), rotation(0) {
    collisionManager = DependencyInjection::Resolve<CollisionManager>();

    if (!collisionManager) {
        std::cerr << "Failed to resolve CollisionManager during Shooter initialization!" << std::endl;
    }
}

Shooter::~Shooter() {
    for (Bullet* bullet : bullets) {

        if (collisionManager) {
            collisionManager->RemoveEntity(bullet);
        }
        delete bullet;
    }
    bullets.clear();
}

void Shooter::Update() {
    for (auto it = bullets.begin(); it != bullets.end();) {
        Bullet* bullet = *it;
        bullet->Update();

        if (!bullet->IsActive()) {

            if (collisionManager) {
                collisionManager->RemoveEntity(bullet);
            }
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

void Shooter::SetPosition(double x, double y) {
    playerX = x;
    playerY = y;
}

void Shooter::AddBullet(Bullet* bullet) {
    bullets.push_back(bullet);

    if (collisionManager) {
        collisionManager->AddEntity(bullet);
    } else {
        std::cerr << "Cannot add bullet to CollisionManager: manager is null!" << std::endl;
    }
}