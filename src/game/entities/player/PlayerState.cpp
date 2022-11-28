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
        switch (input.type) {
            case InputEvent::Type::LEFT:
                player._animated_sprite->start("idle", true, true, false);

                break;

            case InputEvent::Type::RIGHT:
                player._animated_sprite->start("idle", true, false, false);

                break;

            default:
                break;
        }

        return nullptr;
    }
} // game