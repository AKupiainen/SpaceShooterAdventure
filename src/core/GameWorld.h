#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <vector>
#include "GameEntity.h"
#include "../sprites/ParallaxLayer.h"
#include "CollisionManager.h"
#include "../enemy/EnemySpawner.h"

class GameWorld {
public:
    GameWorld(SDL_Renderer* renderer);
    ~GameWorld();

    void AddEntity(GameEntity* entity);
    void AddParallaxLayer(ParallaxLayer* layer);
    void SetCollisionManager(CollisionManager* manager);
    void Update(double deltaTime);
    void Render(SDL_Renderer* renderer) const;

private:
    std::vector<GameEntity*> entities;
    std::vector<GameEntity*> pendingEntities;
    std::vector<ParallaxLayer*> parallaxLayers;

    CollisionManager* collisionManager;
    std::unique_ptr<EnemySpawner> enemySpawner;
};

#endif
