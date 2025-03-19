#include "GameWorld.h"
#include "Time.h"

GameWorld::GameWorld(SDL_Renderer* renderer)
    : collisionManager(nullptr) {
    enemySpawner = std::make_unique<EnemySpawner>(renderer);
}

GameWorld::~GameWorld() {
    for (auto& layer : parallaxLayers) {
        delete layer;
    }

    for (auto& entity : entities) {
        delete entity;
    }
}

void GameWorld::AddEntity(GameEntity* entity) {
    if (entity) {
        pendingEntities.push_back(entity);

        if (collisionManager) {
            collisionManager->AddEntity(entity);
        }
    }
}

void GameWorld::AddParallaxLayer(ParallaxLayer* layer) {
    parallaxLayers.push_back(layer);
}

void GameWorld::SetCollisionManager(CollisionManager* manager) {
    collisionManager = manager;
}

void GameWorld::Update(double deltaTime) {

    enemySpawner->Update(deltaTime);

    for (auto* enemy : enemySpawner->GetSpawnedEnemies()) {
        AddEntity(enemy);
    }

    if (!pendingEntities.empty()) {
        entities.insert(entities.end(), pendingEntities.begin(), pendingEntities.end());
        pendingEntities.clear();
    }

    for (auto it = entities.begin(); it != entities.end();) {
        GameEntity* entity = *it;

        if (entity->IsActive()) {
            entity->Update(Time::GetDeltaTime());
            entity->UpdateCollisionBox();
            ++it;
        } else {
            delete entity;
            it = entities.erase(it);
            collisionManager->RemoveEntity(entity);
        }
    }

    for (auto& layer : parallaxLayers) {
        if (layer) {
            layer->Update(deltaTime);
        }
    }

    if (collisionManager) {
        collisionManager->CheckCollisions();
    }
}

void GameWorld::Render(SDL_Renderer* renderer) const {
    for (auto& layer : parallaxLayers) {
        layer->Render(renderer);
    }

    for (auto& entity : entities) {
        if (entity && entity->IsActive()) {
            entity->Render(renderer);
        }
    }

    if (collisionManager) {
        collisionManager->DrawCollisionBoxes(renderer);
    }
}