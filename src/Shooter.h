#ifndef SHOOTER_H
#define SHOOTER_H

#include <vector>
#include "Bullet.h"
#include "BulletPath.h"
#include <SDL2/SDL.h>

class Shooter {
public:
    Shooter(SDL_Renderer* renderer, int playerX, int playerY);
    ~Shooter();

    void Shoot(BulletPath* path, int bulletWidth, int bulletHeight, const std::string& texturePath, double angle);

    void Update();
    void Render(SDL_Renderer* renderer);
    void SetPosition(int x, int y);

private:
    SDL_Renderer* renderer;
    int playerX;
    int playerY;
    std::vector<Bullet*> bullets;
    float shootCooldown;
    float timeSinceLastShot;
};

#endif