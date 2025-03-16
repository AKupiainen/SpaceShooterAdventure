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
                if (callback) {
                    callback(*entities[i], *entities[j]);
                }
            }
        }
    }
}

void CollisionManager::DrawCollisionBoxes(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (const auto& entity : entities) {
        CollisionBox& box = entity->GetCollisionBox();
        SDL_Rect rect = box.GetRect();
        SDL_RenderDrawRect(renderer, &rect);
    }
}
