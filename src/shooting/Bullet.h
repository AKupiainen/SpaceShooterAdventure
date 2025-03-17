#ifndef BULLET_H
#define BULLET_H

#include "../core/GameEntity.h"
#include "BulletPath.h"
#include <string>

class Bullet : public GameEntity {
public:
    Bullet(SDL_Renderer* renderer, int x, int y, BulletPath* path, int width, int height, const std::string& texturePath);
    ~Bullet() override;

    void Update() override;
    void Render(SDL_Renderer* renderer) override;
    void OnCollisionEnter(GameEntity &other) override;

    [[nodiscard]] bool IsActive() const { return active; }

private:
    BulletPath* path;
    bool active = true;
};

#endif