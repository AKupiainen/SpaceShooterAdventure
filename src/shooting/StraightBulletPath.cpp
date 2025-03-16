#include "StraightBulletPath.h"
#include <cmath>
#include "../core/Time.h"

#define DEG_TO_RAD (M_PI / 180.0)

StraightBulletPath::StraightBulletPath(double speedX, double speedY)
    : speedX(speedX), speedY(speedY) {}

void StraightBulletPath::Update(double& posX, double& posY, double rotationAngle) {
    double deltaTime = Time::GetDeltaTime();

    // Convert angle from degrees to radians
    double radAngle = rotationAngle * DEG_TO_RAD;

    // If rotationAngle is non-zero, adjust the velocity direction accordingly
    double velocityX = speedX * cos(radAngle) - speedY * sin(radAngle);
    double velocityY = speedX * sin(radAngle) + speedY * cos(radAngle);

    // Apply movement update
    posX += velocityX * deltaTime;
    posY += velocityY * deltaTime;
}
