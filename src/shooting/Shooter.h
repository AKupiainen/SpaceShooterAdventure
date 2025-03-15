#include "Bullet.h"
#include <SDL2/SDL.h>
#include <vector>

class Shooter;
class BulletPath;

class Weapon {
public:
    virtual ~Weapon() = default;
    virtual void Shoot(Shooter& shooter) = 0;
};

class Shooter {
public:
    Shooter(SDL_Renderer* renderer, int playerX, int playerY);
    ~Shooter();

    void Shoot(BulletPath* path, int bulletWidth, int bulletHeight, const std::string& texturePath, double angle);
    void Update();
    void Render(SDL_Renderer* renderer) const;

    void SetPosition(int x, int y);
    void SetWeapon(std::unique_ptr<Weapon> weapon);

    float GetTimeSinceLastShot() const;

private:
    SDL_Renderer* renderer;
    int playerX, playerY;
    float shootCooldown;
    float timeSinceLastShot;
    std::vector<Bullet*> bullets;
    std::unique_ptr<Weapon> currentWeapon;
};
