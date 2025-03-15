#include "StraightBulletWeapon.h"
#include "StraightBulletPath.h"
#include "Bullet.h"

StraightBulletWeapon::StraightBulletWeapon(SDL_Renderer* renderer, const std::string& bulletTexturePath, float shootCooldown)
    : bulletTexturePath(bulletTexturePath), bulletWidth(10), bulletHeight(20), shootCooldown(shootCooldown) {
}

void StraightBulletWeapon::Shoot(Shooter& shooter)
{
    // Ensure the shooter is allowed to shoot based on the cooldown
    if (shooter.GetTimeSinceLastShot() >= shootCooldown) {
        // Create a new bullet path (straight)
        BulletPath* path = new StraightBulletPath(bulletWidth, bulletHeight);
        // Shoot the bullet using the shoot method in the Shooter class
        shooter.Shoot(path, bulletWidth, bulletHeight, bulletTexturePath, 270.0);  // Angle 270 for downward movement
    }
}
