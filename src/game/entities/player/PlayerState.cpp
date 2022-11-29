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
        if (input.state_enter) {
            switch (input.type) {
                case InputEvent::Type::LEFT:
                    player._animated_sprite->setMirrorH(true);

                    break;

                case InputEvent::Type::RIGHT:
                    player._animated_sprite->setMirrorH(false);

                    break;

                default:
                    break;
            }
        }

        return nullptr;
    }
} // game