#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <vector>
#include "GameEntity.h"
#include <SDL2/SDL.h>

class CollisionManager {
public:
    using CollisionCallback = void(*)(GameEntity& entity1, GameEntity& entity2);

    void AddEntity(GameEntity* entity);
    void RemoveEntity(const GameEntity* entity);
    void RegisterCallback(CollisionCallback callback);
    void CheckCollisions() const;
    void DrawCollisionBoxes(SDL_Renderer* renderer) const;

    bool Contains(const GameEntity* entity) const;

    size_t GetEntityCount() const { return entities.size(); }

private:
    std::vector<GameEntity*> entities;
    CollisionCallback callback = nullptr;
};

inline void CollisionManager::RemoveEntity(const GameEntity* entity) {
    if (auto it = std::find(entities.begin(), entities.end(), entity); it != entities.end()) {
        entities.erase(it);
    }
}

inline bool CollisionManager::Contains(const GameEntity* entity) const {
    return std::find(entities.begin(), entities.end(), entity) != entities.end();
}

#endif