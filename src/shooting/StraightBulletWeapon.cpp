#include "StraightBulletWeapon.h"
#include "Shooter.h"
#include "Bullet.h"
#include "StraightBulletPath.h"

StraightBulletWeapon::StraightBulletWeapon(const std::string& bulletTexturePath, int bulletWidth, int bulletHeight)
    : bulletTexturePath(bulletTexturePath), bulletWidth(bulletWidth), bulletHeight(bulletHeight) {
}

void StraightBulletWeapon::Fire(Shooter& shooter)
{
    auto* path = new StraightBulletPath(0, -10);

    auto* bullet = new Bullet(
        shooter.GetRenderer(),
        shooter.GetX(),
        shooter.GetY(),
        path,
        bulletWidth,
        bulletHeight,
        bulletTexturePath
    );

    bullet->SetRotation(270.0);
    shooter.AddBullet(bullet);
}