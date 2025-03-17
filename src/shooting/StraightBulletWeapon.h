#pragma once

#include "Weapon.h"
#include <string>

class Shooter;

class StraightBulletWeapon : public Weapon {
public:
    explicit StraightBulletWeapon(std::string  bulletTexturePath, int bulletWidth = 10, int bulletHeight = 20);
    ~StraightBulletWeapon() override = default;

    void Fire(Shooter& shooter) override;

private:
    std::string bulletTexturePath;
    int bulletWidth;
    int bulletHeight;
};