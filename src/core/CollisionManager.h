#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <vector>
#include "GameEntity.h"
#include <SDL2/SDL.h>

class CollisionManager {
public:
    using CollisionCallback = void(*)(GameEntity& entity1, GameEntity& entity2);

    void AddEntity(GameEntity* entity);
    void RegisterCallback(CollisionCallback callback);
    void CheckCollisions() const;
    void DrawCollisionBoxes(SDL_Renderer* renderer) const;

private:
    std::vector<GameEntity*> entities;
    CollisionCallback callback = nullptr;
};

#endif
