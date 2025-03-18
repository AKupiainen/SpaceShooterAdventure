#include "GameWorld.h"
#include <algorithm>
#include <ostream>

GameWorld::GameWorld() {}

GameWorld::~GameWorld() {

    for (auto layer : parallaxLayers) {
        delete layer;
    }
}

void GameWorld::Update(float deltaTime) {

    for (auto& entity : entities) {
        if (entity) {
            entity->Update(deltaTime);
            entity->UpdateCollisionBox();
        }
    }


    for (auto& layer : parallaxLayers) {
        layer->Update(deltaTime);
    }

    entities.erase(
        std::remove_if(entities.begin(), entities.end(),
            [](const std::unique_ptr<GameEntity>& e) { return !e->IsActive(); }),
        entities.end());
}

void GameWorld::Render(SDL_Renderer* renderer) const {
    for (auto& layer : parallaxLayers) {
        layer->Render(renderer);
    }

    for (auto& entity : entities) {
        if (entity) {
            entity->Render(renderer);
        }
    }
}

void GameWorld::AddEntity(std::unique_ptr<GameEntity> entity) {
    if (entity) {
        entities.push_back(std::move(entity));
    }
}

void GameWorld::AddParallaxLayer(ParallaxLayer* layer) {
    parallaxLayers.push_back(layer);
}

void GameWorld::Clear() {

    entities.clear();

    for (auto layer : parallaxLayers) {
        delete layer;
    }
    parallaxLayers.clear();
}