#include "CollisionManager.h"
#include "QuadTree.h"
#include <SDL2/SDL.h>

CollisionManager::CollisionManager(const std::shared_ptr<GameSettings> &settings)
    : gameSettings(settings)
{}

void CollisionManager::CheckCollisions() const {

    int screenWidth = gameSettings->GetWindowWidth();
    int screenHeight = gameSettings->GetWindowHeight();

    const CollisionBox worldBounds(0, 0, screenWidth, screenHeight);
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

    int screenWidth = gameSettings->GetWindowWidth();
    int screenHeight = gameSettings->GetWindowHeight();

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (const auto& entity : entities) {
        CollisionBox& box = entity->GetCollisionBox();
        SDL_Rect rect = box.GetRect();
        SDL_RenderDrawRect(renderer, &rect);
    }

    CollisionBox worldBounds(0, 0, screenWidth, screenHeight);
    QuadTree quadTree(0, worldBounds);

    for (auto& entity : entities) {
        quadTree.Insert(entity);
    }

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    quadTree.Draw(renderer);
}