#include "Tile.h"

namespace game {
    Tile::Tile(engine::Transform transform, const std::shared_ptr<engine::ISpriteComponent> &sprite)
            : engine::Entity(std::move(transform)) {
        addComponent(sprite);
    }
} // game