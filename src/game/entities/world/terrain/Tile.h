#ifndef GAME_ENGINE_TILE_H
#define GAME_ENGINE_TILE_H

#include "engine/entity/Entity.h"
#include "engine/entity/components/view/sprite/ISpriteComponent.h"
#include "engine/entity/components/view/sprite/IAnimatedSpriteComponent.h"

namespace game {

    class Tile : public engine::Entity {
    public:
        Tile(engine::Transform transform, const std::shared_ptr<engine::ISpriteComponent>& sprite);
    };

    class AnimatedTile : public engine::Entity {
    public:
        AnimatedTile(engine::Transform transform, const std::shared_ptr<engine::IAnimatedSpriteComponent>& sprite);
    };

} // game


#endif //GAME_ENGINE_TILE_H
