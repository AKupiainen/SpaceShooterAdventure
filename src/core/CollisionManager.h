#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <vector>
#include "GameEntity.h"
#include <SDL2/SDL.h>

class CollisionManager {
public:
    void AddEntity(GameEntity* entity);
    void RemoveEntity(const GameEntity* entity);
    void CheckCollisions() const;
    void DrawCollisionBoxes(SDL_Renderer* renderer) const;

    bool Contains(const GameEntity* entity) const;

    size_t GetEntityCount() const { return entities.size(); }

private:
    std::vector<GameEntity*> entities;
};

inline void CollisionManager::RemoveEntity(const GameEntity* entity) {
    if (const auto it = std::find(entities.begin(), entities.end(), entity); it != entities.end()) {
        entities.erase(it);
    }
}

inline bool CollisionManager::Contains(const GameEntity* entity) const {
    return std::find(entities.begin(), entities.end(), entity) != entities.end();
}

#endif
