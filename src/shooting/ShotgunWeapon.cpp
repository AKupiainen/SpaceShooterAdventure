#include "ShotgunWeapon.h"

#include "Shooter.h"
#include "Bullet.h"
#include "StraightBulletPath.h"

ShotgunWeapon::ShotgunWeapon(std::string  bulletTexturePath, int bulletWidth, int bulletHeight, float spreadAngle, int bulletsToFire)
    : bulletTexturePath(std::move(bulletTexturePath)),
      bulletWidth(bulletWidth),
      bulletHeight(bulletHeight),
      spreadAngle(spreadAngle),
      bulletsToFire(bulletsToFire) {}

void ShotgunWeapon::Fire(Shooter& shooter)
{
    double shooterAngle = shooter.GetRotation();
    double angleIncrement = spreadAngle / static_cast<double>(bulletsToFire - 1);

    for (int i = 0; i < bulletsToFire; ++i) {
        double speed = 600.0f;
        double offsetAngle = shooterAngle - spreadAngle / 2.0f + i * angleIncrement;
        double radians = offsetAngle * M_PI / 180.0f;

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

        bullet->SetRotation(static_cast<int>(offsetAngle));
        shooter.AddBullet(std::unique_ptr<Bullet>(bullet));
    }
}