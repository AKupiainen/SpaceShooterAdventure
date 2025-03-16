#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <vector>
#include <algorithm>
#include "GameEntity.h"
#include <SDL2/SDL.h>

class CollisionManager {
public:
    using CollisionCallback = void(*)(GameEntity& entity1, GameEntity& entity2);

    void AddEntity(GameEntity* entity);
    void RemoveEntity(GameEntity* entity);
    void RegisterCallback(CollisionCallback callback);
    void CheckCollisions() const;
    void DrawCollisionBoxes(SDL_Renderer* renderer) const;

    bool Contains(GameEntity* entity) const;

    size_t GetEntityCount() const { return entities.size(); }

private:
    std::vector<GameEntity*> entities;
    CollisionCallback callback = nullptr;
};

// Implementation for the new methods

inline void CollisionManager::RemoveEntity(GameEntity* entity) {
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end()) {
        entities.erase(it);
    }
}

inline bool CollisionManager::Contains(GameEntity* entity) const {
    return std::find(entities.begin(), entities.end(), entity) != entities.end();
}

#endif