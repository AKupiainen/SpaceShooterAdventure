#include "ShotgunWeapon.h"
#include "Shooter.h"
#include "Bullet.h"
#include "StraightBulletPath.h"

ShotgunWeapon::ShotgunWeapon(const std::string& bulletTexturePath, int bulletWidth, int bulletHeight, float spreadAngle, int bulletsToFire)
    : bulletTexturePath(bulletTexturePath),
      bulletWidth(bulletWidth),
      bulletHeight(bulletHeight),
      spreadAngle(spreadAngle),
      bulletsToFire(bulletsToFire) {}

void ShotgunWeapon::Fire(Shooter& shooter)
{
    float speed = 600.0f;
    float shooterAngle = shooter.GetRotation();
    float angleIncrement = spreadAngle / (bulletsToFire - 1);

    for (int i = 0; i < bulletsToFire; ++i) {
        float offsetAngle = shooterAngle - spreadAngle / 2.0f + i * angleIncrement;
        float radians = offsetAngle * M_PI / 180.0f;

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

        bullet->SetRotation(offsetAngle);
        shooter.AddBullet(bullet);
    }
}
