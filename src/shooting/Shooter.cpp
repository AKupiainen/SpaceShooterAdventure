#include "Shooter.h"
#include "Bullet.h"
#include "../core/Time.h"
#include <iostream>
#include "../core/DependencyInjection.h"
#include "../core/GameWorld.h"

Shooter::Shooter(SDL_Renderer* renderer, int x, int y)
    : renderer(renderer), playerX(x),
      playerY(y) {

    gameWorld = DependencyInjection::Resolve<GameWorld>();

    if (!gameWorld) {
        std::cerr << "Failed to resolve GameWorld during Shooter initialization!" << std::endl;
    }
}

Shooter::~Shooter() { }

void Shooter::Update() {
    timeSinceLastShot += Time::GetDeltaTime();

    if (currentWeapon && timeSinceLastShot >= shootCooldown) {
        currentWeapon->Fire(*this);
        timeSinceLastShot = 0.0f;
    }
}

void Shooter::SetWeapon(Weapon* weaponPtr) {
    currentWeapon = weaponPtr;
}

void Shooter::SetPosition(double x, double y) {
    playerX = x;
    playerY = y;
}

void Shooter::AddBullet(std::unique_ptr<Bullet> bullet) const {

    if (gameWorld) {
        gameWorld->AddEntity(std::move(bullet));
    } else {
        std::cerr << "Cannot add bullet: GameWorld is null!" << std::endl;
    }
}