#include "QuadTree.h"

QuadTree::QuadTree(int level, const CollisionBox& bounds)
    : level(level), bounds(bounds) {
    entities.reserve(4);
}

QuadTree::~QuadTree() {
    DeleteNodes();
}

QuadTree::QuadTree(QuadTree&& other) noexcept
    : level(other.level), bounds(std::move(other.bounds)),
      entities(std::move(other.entities)), nodes(std::move(other.nodes)) {
    other.nodes.clear();
}

QuadTree& QuadTree::operator=(QuadTree&& other) noexcept {
    if (this != &other) {
        level = other.level;
        bounds = std::move(other.bounds);
        entities = std::move(other.entities);
        nodes = std::move(other.nodes);
        other.nodes.clear();
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
        if (node->IsEntityWithinBounds(entity)) {
            node->Insert(entity);
        }
    }
}

auto QuadTree::Retrieve(std::vector<GameEntity *> &potentialCollisions, GameEntity *entity) -> void {
    if (!IsEntityWithinBounds(entity)) {
        return;
    }

    potentialCollisions.insert(potentialCollisions.end(), entities.begin(), entities.end());

    if (!nodes.empty()) {
        SDL_Rect entityRect = entity->GetCollisionBox().GetRect();
        for (auto& node : nodes) {
            SDL_Rect nodeRect = node->bounds.GetRect();
            if (SDL_HasIntersection(&entityRect, &nodeRect)) {
                node->Retrieve(potentialCollisions, entity);
            }
        }
    }
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

    if (subWidth < 10 || subHeight < 10) return;

    nodes.reserve(4);
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

auto QuadTree::Draw(SDL_Renderer *renderer) const -> void {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect rect = bounds.GetRect();
    SDL_RenderDrawRect(renderer, &rect);

    for (const auto& node : nodes) {
        node->Draw(renderer);
    }
}