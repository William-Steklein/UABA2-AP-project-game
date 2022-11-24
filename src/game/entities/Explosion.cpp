#include "Explosion.h"

namespace game {
    Explosion::Explosion(const engine::Transform &transform,
                         std::shared_ptr<engine::AnimationComponent> animation,
                         std::shared_ptr<engine::IAudioComponent> audio)
            : engine::Entity(transform, nullptr, std::move(animation), std::move(audio)) {
        checkComponent(_view);
        checkComponent(_animation);
        checkComponent(_audio);
        _animation->start("circle_explosion", false, false, false);
//        _audio->playSound("footstep", 0, true);
        _audio->playSound("scream", 1, true);
//        _audio->playMusic("portal_radio", 0, true);
    }

    void Explosion::update(double t, float dt) {
        if (_animation->isFinished()) {
            _animation->start("ground_explosion", true, false, false);
        }

        if (_animation->isLoopFinished()) {
//            _animation->setMirrorV(!_animation->getMirrorV());
            setRotation(_transform.rotation + static_cast<float>(M_PI) / 4);
        }

        Entity::update(t, dt);
    }
} // game