#include "PlayerState.h"

namespace game {
    IdleState::IdleState() {

    }

    void IdleState::enter(Player &player) {
        player._animated_sprite->start("idle", true, false, false);
    }

    void IdleState::update(Player &player) {

    }

    std::shared_ptr<IPlayerState> IdleState::handleInput(Player &player, const std::string &input) {

        return nullptr;
    }
} // game