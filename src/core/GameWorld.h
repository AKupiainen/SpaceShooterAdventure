#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "../sprites/ParallaxLayer.h"
#include "../core/GameEntity.h"

class GameWorld {
    std::vector<std::unique_ptr<GameEntity>> entities;
    std::vector<ParallaxLayer*> parallaxLayers;

public:
    GameWorld();
    ~GameWorld();

    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer) const;
    void AddEntity(std::unique_ptr<GameEntity> entity);
    void AddParallaxLayer(ParallaxLayer* layer);

    void Clear();

    const std::vector<std::unique_ptr<GameEntity>>& getEntities() const {
        return entities;
    }
};