#include "QuadTree.h"

QuadTree::QuadTree(int level, const CollisionBox& bounds)
    : level(level), bounds(bounds) {}

QuadTree::~QuadTree() {
    DeleteNodes();
}

QuadTree::QuadTree(QuadTree&& other) noexcept
    : level(other.level), bounds(other.bounds), entities(std::move(other.entities)), nodes(std::move(other.nodes)) {
    other.level = 0;
}

QuadTree& QuadTree::operator=(QuadTree&& other) noexcept {
    if (this != &other) {
        DeleteNodes();
        level = other.level;
        bounds = other.bounds;
        entities = std::move(other.entities);
        nodes = std::move(other.nodes);
        other.level = 0;
    }
    return *this;
}

void QuadTree::Insert(GameEntity* entity) {
    if (!IsEntityWithinBounds(entity)) {
        return;
    }

    if (entities.size() < 4 || level > 5) {
        entities.push_back(entity);
        return;
    }

    if (nodes.empty()) {
        Subdivide();
    }

    for (auto& node : nodes) {
        node->Insert(entity);
    }
}

void QuadTree::Retrieve(std::vector<GameEntity*>& potentialCollisions, GameEntity* entity) {
    if (!IsEntityWithinBounds(entity)) {
        return;
    }

    SDL_Rect entityRect = entity->GetCollisionBox().GetRect();
    for (auto& node : nodes) {
        SDL_Rect nodeRect = node->bounds.GetRect();
        if (SDL_HasIntersection(&entityRect, &nodeRect)) {
            node->Retrieve(potentialCollisions, entity);
        }
    }

    potentialCollisions.insert(potentialCollisions.end(), entities.begin(), entities.end());
}

bool QuadTree::IsEntityWithinBounds(GameEntity* entity) const {
    SDL_Rect entityRect = entity->GetCollisionBox().GetRect();
    SDL_Rect boundsRect = bounds.GetRect();
    return SDL_HasIntersection(&entityRect, &boundsRect);
}

void QuadTree::Subdivide() {
    int subWidth = bounds.GetRect().w / 2;
    int subHeight = bounds.GetRect().h / 2;
    int x = bounds.GetRect().x;
    int y = bounds.GetRect().y;

    nodes.push_back(new QuadTree(level + 1, CollisionBox(x, y, subWidth, subHeight)));
    nodes.push_back(new QuadTree(level + 1, CollisionBox(x + subWidth, y, subWidth, subHeight)));
    nodes.push_back(new QuadTree(level + 1, CollisionBox(x, y + subHeight, subWidth, subHeight)));
    nodes.push_back(new QuadTree(level + 1, CollisionBox(x + subWidth, y + subHeight, subWidth, subHeight)));
}

void QuadTree::DeleteNodes() {
    for (auto node : nodes) {
        delete node;
    }
    nodes.clear();
}
