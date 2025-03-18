#include "StraightBulletWeapon.h"

#include <iostream>
#include "Shooter.h"
#include "Bullet.h"
#include "StraightBulletPath.h"

StraightBulletWeapon::StraightBulletWeapon(std::string  bulletTexturePath, int bulletWidth, int bulletHeight)
    : bulletTexturePath(std::move(bulletTexturePath)), bulletWidth(bulletWidth), bulletHeight(bulletHeight) {
}

void StraightBulletWeapon::Fire(Shooter& shooter)
{
    double speed = 300.0f;

    double shooterAngle = shooter.GetRotation();
    double radians = shooterAngle * M_PI / 180.0f;

    double dx = speed * std::sin(radians);
    double dy = -speed * std::cos(radians);

    auto* path = new StraightBulletPath(dx, dy);

    auto* bullet = new Bullet(
        shooter.GetRenderer(),
        shooter.GetX(),
        shooter.GetY(),
        path,
        bulletWidth,
        bulletHeight,
        bulletTexturePath
    );

    bullet->SetRotation(static_cast<int>(shooterAngle));
    shooter.AddBullet(std::unique_ptr<Bullet>(bullet));
}