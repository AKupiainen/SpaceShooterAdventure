#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include "GameEntity.h"

class QuadTree {
public:
    QuadTree(int level, const CollisionBox& bounds);
    ~QuadTree();

    QuadTree(const QuadTree& other) = delete;
    QuadTree& operator=(const QuadTree& other) = delete;
    QuadTree(QuadTree&& other) noexcept;
    QuadTree& operator=(QuadTree&& other) noexcept;

    void Insert(GameEntity* entity);
    void Retrieve(std::vector<GameEntity*>& potentialCollisions, GameEntity* entity);

private:
    int level;
    CollisionBox bounds;
    std::vector<GameEntity*> entities;
    std::vector<QuadTree*> nodes;

    void Subdivide();
    bool IsEntityWithinBounds(GameEntity* entity) const;
    void DeleteNodes();
};

#endif
