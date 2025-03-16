#include "StraightBulletWeapon.h"

#include <iostream>
#include "Shooter.h"
#include "Bullet.h"
#include "StraightBulletPath.h"

StraightBulletWeapon::StraightBulletWeapon(const std::string& bulletTexturePath, int bulletWidth, int bulletHeight)
    : bulletTexturePath(bulletTexturePath), bulletWidth(bulletWidth), bulletHeight(bulletHeight) {
}

void StraightBulletWeapon::Fire(Shooter& shooter)
{
    float speed = 300.0f;

    float shooterAngle = shooter.GetRotation();
    float radians = shooterAngle * M_PI / 180.0f;

    float dx = speed * std::sin(radians);
    float dy = -speed * std::cos(radians);

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

    bullet->SetRotation(shooterAngle);
    shooter.AddBullet(bullet);
}