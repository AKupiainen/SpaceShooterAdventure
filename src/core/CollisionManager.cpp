#include "CollisionManager.h"
#include <iostream>

void CollisionManager::AddEntity(GameEntity* entity) {
    entities.push_back(entity);
}

void CollisionManager::RegisterCallback(CollisionCallback callback) {
    this->callback = callback;
}

void CollisionManager::CheckCollisions() const {
    for (size_t i = 0; i < entities.size(); ++i) {
        for (size_t j = i + 1; j < entities.size(); ++j) {

            if (entities[i]->CheckCollision(*entities[j])) {
                callback(*entities[i], *entities[j]);
            }
        }
    }
}