#include "Tile.h"

namespace game {
    Tile::Tile(engine::Transform transform, const std::shared_ptr<engine::ISpriteComponent> &sprite)
            : engine::Entity(std::move(transform)) {
        addComponent(sprite);
    }

    AnimatedTile::AnimatedTile(engine::Transform transform,
                               const std::shared_ptr<engine::IAnimatedSpriteComponent> &sprite)
            : engine::Entity(std::move(transform)) {
        addComponent(sprite);

        sprite->start("default", true);
    }
} // game