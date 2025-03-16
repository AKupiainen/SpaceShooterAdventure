#pragma once
#include <string>

#include "Weapon.h"

class ShotgunWeapon : public Weapon {
public:
    ShotgunWeapon(const std::string& bulletTexturePath, int bulletWidth, int bulletHeight, float spreadAngle, int bulletsToFire);
    void Fire(Shooter& shooter) override;

private:
    std::string bulletTexturePath;
    int bulletWidth;
    int bulletHeight;
    float spreadAngle;
    int bulletsToFire;
};