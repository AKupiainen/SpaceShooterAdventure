#include "StraightBulletPath.h"
#include <cmath>
#include "../core/Time.h"

#define DEG_TO_RAD (M_PI / 180.0)

StraightBulletPath::StraightBulletPath(double speedX, double speedY)
    : speedX(speedX), speedY(speedY) {}

void StraightBulletPath::Update(double& posX, double& posY, double rotationAngle) {
    double deltaTime = Time::GetDeltaTime();

    double radAngle = rotationAngle * DEG_TO_RAD;

    double velocityX = speedX * cos(radAngle) - speedY * sin(radAngle);
    double velocityY = speedX * sin(radAngle) + speedY * cos(radAngle);

    posX += velocityX * deltaTime;
    posY += velocityY * deltaTime;
}
