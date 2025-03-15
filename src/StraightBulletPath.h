#ifndef STRAIGHTBULLETPATH_H
#define STRAIGHTBULLETPATH_H

#include "BulletPath.h"

class StraightBulletPath : public BulletPath {
public:
    // Constructor to initialize speed values for X and Y
    StraightBulletPath(double speedX, double speedY);

    // Override the Update method to move the bullet in a straight line
    void Update(double& posX, double& posY, double rotationAngle) override;

private:
    double speedX; // Speed along the X-axis
    double speedY; // Speed along the Y-axis
};

#endif // STRAIGHTBULLETPATH_H
