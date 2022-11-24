#include "Player.h"

namespace game {
    Player::Player(const engine::Transform &transform, std::shared_ptr<engine::IViewComponent> view,
                   std::shared_ptr<engine::AnimationComponent> animation, std::shared_ptr<engine::IAudioComponent> audio)
            : Entity(transform, std::move(view), std::move(animation), std::move(audio)) {
        checkComponent(_audio);

        _audio->playSound("footstep", 0, true);
    }

    void Player::update(double t, float dt) {
        Entity::update(t, dt);
    }
} // game