#include "Shooter.h"
#include "../core/GameWorld.h"
#include "../core/Time.h"

Shooter::Shooter(SDL_Renderer* renderer, int x, int y)
    : currentWeapon(nullptr), renderer(renderer), playerX(x),
      playerY(y), shootCooldown(0.5f), timeSinceLastShot(0.0f), rotation(0) {
}

Shooter::~Shooter() {}

void Shooter::Update() {
    if (currentWeapon && timeSinceLastShot >= shootCooldown) {
        currentWeapon->Fire(*this);
        timeSinceLastShot = 0.0f;
    }

    timeSinceLastShot += Time::GetDeltaTime();
}

void Shooter::SetPosition(double x, double y) {
    playerX = x;
    playerY = y;
}