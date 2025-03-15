#ifndef STRAIGHTBULLETWEAPON_H
#define STRAIGHTBULLETWEAPON_H

#include <string>
#include <SDL2/SDL.h>

#include "Shooter.h"

class StraightBulletWeapon : public Weapon {
public:
    StraightBulletWeapon(SDL_Renderer* renderer, const std::string& bulletTexturePath, float shootCooldown);
    ~StraightBulletWeapon() override = default;

    void Shoot(Shooter& shooter) override;

private:
    std::string bulletTexturePath;
    int bulletWidth;
    int bulletHeight;
    float shootCooldown;
};

#endif
