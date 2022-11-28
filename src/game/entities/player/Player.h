#ifndef GAME_ENGINE_PLAYER_H
#define GAME_ENGINE_PLAYER_H


#include <engine/entity/Entity.h>
#include <engine/entity/components/view/sprite/IAnimatedSpriteComponent.h>

#include "game/entities/player/IPlayerState.h"

namespace game {

    class Player : public engine::Entity {
    public:
        std::shared_ptr<engine::IAnimatedSpriteComponent> _animated_sprite;

        Player(engine::Transform transform, std::shared_ptr<IPlayerState> state,
               std::shared_ptr<engine::IAnimatedSpriteComponent> animated_sprite);

        ~Player() override = default;

        void update(double t, float dt) override;

        void handleInput(const std::string &input) override;

    private:
        std::shared_ptr<IPlayerState> _state;
    };

} // game

#endif //GAME_ENGINE_PLAYER_H
