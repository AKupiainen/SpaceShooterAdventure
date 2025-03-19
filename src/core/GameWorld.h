#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <vector>
#include "GameEntity.h"
#include "../sprites/ParallaxLayer.h"
#include "CollisionManager.h"

class GameWorld {
public:
    GameWorld();
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
};

#endif
