#ifndef BULLETPATH_H
#define BULLETPATH_H

class BulletPath {
public:
    virtual ~BulletPath() = default;
    virtual void Update(double& posX, double& posY, double rotationAngle) = 0;
};

#endif