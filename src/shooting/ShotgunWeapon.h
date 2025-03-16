#pragma once
#include <string>

#include "Weapon.h"

class ShotgunWeapon : public Weapon {
public:
    ShotgunWeapon(const std::string& bulletTexturePath, int bulletWidth, int bulletHeight, float spreadAngle = 15.0f, int bulletsToFire = 5);
    virtual void Fire(Shooter& shooter) override;

private:
    std::string bulletTexturePath;
    int bulletWidth;
    int bulletHeight;
    float spreadAngle;
    int bulletsToFire;
};