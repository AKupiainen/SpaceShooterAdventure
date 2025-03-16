#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include "GameEntity.h"

class QuadTree {
public:
    QuadTree(int level, const CollisionBox& bounds);

    void Insert(GameEntity* entity);
    void Retrieve(std::vector<GameEntity*>& potentialCollisions, GameEntity* entity);

private:
    int level;
    CollisionBox bounds;
    std::vector<GameEntity*> entities;
    std::vector<QuadTree*> nodes;

    void Subdivide();
    bool IsEntityWithinBounds(GameEntity* entity) const;
};

#endif
