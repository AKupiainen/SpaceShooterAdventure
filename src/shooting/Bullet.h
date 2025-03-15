#ifndef BULLET_H
#define BULLET_H

#include "../core/GameEntity.h"
#include "BulletPath.h"
#include <string>

class Bullet : public GameEntity {
public:
    Bullet(SDL_Renderer* renderer, int x, int y, BulletPath* path, int width, int height, const std::string& texturePath);
    ~Bullet();

    void Update();
    void Render(SDL_Renderer* renderer);

    // Check if the bullet is still active (in screen or not)
    bool IsActive() const { return active; }

private:
    BulletPath* path;
    bool active = true;
};

#endif