#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <vector>
#include <functional>
#include "GameEntity.h"

class CollisionManager {
public:

    using CollisionCallback = std::function<void(GameEntity&, GameEntity&)>;

    CollisionManager() = default;
    ~CollisionManager() = default;

    void AddEntity(GameEntity* entity);
    void RegisterCallback(CollisionCallback callback);
    void CheckCollisions() const;

private:
    std::vector<GameEntity*> entities;
    CollisionCallback callback;
};

#endif