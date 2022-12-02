#include "PlayerState.h"

namespace game {
    IdleState::IdleState() {

    }

    void IdleState::enter(Player &player) {
        player._animated_sprite->start("idle", true, false, false);
    }

    void IdleState::update(Player &player) {

    }

    std::shared_ptr<IPlayerState> IdleState::handleInput(Player &player, const InputEvent &input) {
        float movement_force = 0.1f;

        if (input.state_enter) {
            switch (input.type) {
                case InputEvent::Type::LEFT:
                    player._physicsComponent->addVelocity({-movement_force, 0});
                    player._animated_sprite->setMirrorH(true);

                    break;

                case InputEvent::Type::RIGHT:
                    player._physicsComponent->addVelocity({movement_force, 0});
                    player._animated_sprite->setMirrorH(false);

                    break;

                case InputEvent::Type::DOWN:
                    player._physicsComponent->addVelocity({0, -movement_force});
                    break;

                case InputEvent::Type::UP:
                    player._physicsComponent->addVelocity({0, movement_force});
                    break;

                default:
                    break;
            }
        }

        return nullptr;
    }
} // game