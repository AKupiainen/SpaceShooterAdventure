#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <unordered_set>
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
    std::unordered_set<GameEntity*> entities;
};

inline void CollisionManager::AddEntity(GameEntity* entity) {
    entities.insert(entity);
}

inline void CollisionManager::RemoveEntity(const GameEntity* entity) {
    if (auto it = entities.find(const_cast<GameEntity*>(entity)); it != entities.end()) {
        entities.erase(it);
    }
}

inline bool CollisionManager::Contains(const GameEntity* entity) const {
    return entities.find(const_cast<GameEntity*>(entity)) != entities.end();
}

#endif