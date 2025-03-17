#include "QuadTree.h"
#include <stack>
#include <queue>

QuadTree::QuadTree(int level, const CollisionBox& bounds)
    : level(level), bounds(bounds) {
    entities.reserve(4);
}

QuadTree::~QuadTree() {
    DeleteNodes();
}

QuadTree::QuadTree(QuadTree&& other) noexcept
    : level(other.level), bounds(other.bounds),
      entities(std::move(other.entities)), nodes(std::move(other.nodes)) {
    other.nodes.clear();
}

QuadTree& QuadTree::operator=(QuadTree&& other) noexcept {
    if (this != &other) {
        DeleteNodes();
        level = other.level;
        bounds = other.bounds;
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

    std::stack<QuadTree*> stack;
    stack.push(this);

    while (!stack.empty()) {
        QuadTree* current = stack.top();
        stack.pop();

        if (current->entities.size() < 4 || current->level > 5) {
            current->entities.push_back(entity);
            return;
        }

        if (current->nodes.empty()) {
            current->Subdivide();
        }

        for (auto& node : current->nodes) {
            if (node->IsEntityWithinBounds(entity)) {
                stack.push(node);
                break;
            }
        }
    }
}

void QuadTree::Retrieve(std::vector<GameEntity *> &potentialCollisions, GameEntity *entity) {
    if (!IsEntityWithinBounds(entity)) {
        return;
    }

    std::queue<QuadTree*> queue;
    queue.push(this);

    while (!queue.empty()) {
        QuadTree* current = queue.front();
        queue.pop();

        potentialCollisions.insert(potentialCollisions.end(), current->entities.begin(), current->entities.end());

        if (!current->nodes.empty()) {
            SDL_Rect entityRect = entity->GetCollisionBox().GetRect();
            for (auto& node : current->nodes) {
                SDL_Rect nodeRect = node->bounds.GetRect();
                if (SDL_HasIntersection(&entityRect, &nodeRect)) {
                    queue.push(node);
                }
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

    if (subWidth < 10 || subHeight < 10) {
        return;
    }

    nodes.reserve(4);
    nodes.emplace_back(new QuadTree(level + 1, CollisionBox(x, y, subWidth, subHeight)));
    nodes.emplace_back(new QuadTree(level + 1, CollisionBox(x + subWidth, y, subWidth, subHeight)));
    nodes.emplace_back(new QuadTree(level + 1, CollisionBox(x, y + subHeight, subWidth, subHeight)));
    nodes.emplace_back(new QuadTree(level + 1, CollisionBox(x + subWidth, y + subHeight, subWidth, subHeight)));
}

void QuadTree::DeleteNodes() {
    for (auto& node : nodes) {
        delete node;
    }
    nodes.clear();
}

void QuadTree::Draw(SDL_Renderer *renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    std::stack<const QuadTree*> stack;
    stack.push(this);

    while (!stack.empty()) {
        const QuadTree* current = stack.top();
        stack.pop();

        SDL_Rect rect = current->bounds.GetRect();
        SDL_RenderDrawRect(renderer, &rect);

        for (const auto& node : current->nodes) {
            if (node) {
                stack.push(node);
            }
        }
    }
}