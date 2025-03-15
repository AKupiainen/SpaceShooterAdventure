#ifndef STRAIGHTBULLETPATH_H
#define STRAIGHTBULLETPATH_H

#include "BulletPath.h"

class StraightBulletPath : public BulletPath {
public:
    StraightBulletPath(double speedX, double speedY);
    void Update(double& posX, double& posY, double rotationAngle) override;

private:
    double speedX;
    double speedY;
};

#endif
