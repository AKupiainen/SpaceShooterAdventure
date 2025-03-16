#include "CollisionManager.h"
#include "QuadTree.h"
#include <SDL2/SDL.h>

void CollisionManager::AddEntity(GameEntity* entity) {
    if (std::find(entities.begin(), entities.end(), entity) == entities.end()) {
        entities.push_back(entity);
    }
}

void CollisionManager::CheckCollisions() const {
    int screenWidth = 1920;
    int screenHeight = 1080;

    CollisionBox worldBounds(0, 0, screenWidth, screenHeight);
    QuadTree quadTree(0, worldBounds);

    for (auto& entity : entities) {
        quadTree.Insert(entity);
    }

    for (auto& entity : entities) {
        std::vector<GameEntity*> potentialCollisions;
        quadTree.Retrieve(potentialCollisions, entity);

        for (auto& otherEntity : potentialCollisions) {
            if (entity != otherEntity && entity->CheckCollision(*otherEntity)) {
                entity->OnCollisionEnter(*otherEntity);
                otherEntity->OnCollisionEnter(*entity);
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
