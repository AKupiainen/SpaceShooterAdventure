#include "StraightBulletPath.h"
#include <cmath>

#define DEG_TO_RAD (M_PI / 180.0)  // Convert degrees to radians

StraightBulletPath::StraightBulletPath(double speedX, double speedY)
    : speedX(speedX), speedY(speedY) {}

void StraightBulletPath::Update(double& posX, double& posY, double rotationAngle) {
    double radians = rotationAngle * DEG_TO_RAD;

    posX += speedX * std::cos(radians);  // Move in the direction of the angle
    posY += speedY * std::sin(radians);
}
