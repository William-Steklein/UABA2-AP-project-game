#ifndef GAME_ENGINE_PLAYER_H
#define GAME_ENGINE_PLAYER_H


#include <engine/entity/Entity.h>
#include <engine/entity/components/view/sprite/IAnimatedSpriteComponent.h>
#include <engine/entity/components/physics/PhysicsComponent.h>

#include "game/input/InputEvent.h"

namespace game {

    class IPlayerState;

    class Player : public engine::Entity {
    public:
        std::shared_ptr<engine::IAnimatedSpriteComponent> _animated_sprite;
        std::shared_ptr<engine::PhysicsComponent> _physicsComponent;

        Player(engine::Transform transform,
               std::shared_ptr<engine::IAnimatedSpriteComponent> animated_sprite);

        ~Player() override = default;

        void update(double t, float dt) override;

        void handleInput(const InputEvent &input);

    private:
        std::shared_ptr<IPlayerState> _state;
    };

} // game

#endif //GAME_ENGINE_PLAYER_H
