#include "Explosion.h"

namespace game {
    Explosion::Explosion(const engine::Transform &transform,
                         std::shared_ptr<engine::AnimationComponent> animation)
            : engine::Entity(transform, nullptr, std::move(animation)) {
        checkComponent(_view);
        checkComponent(_animation);
        _animation->start("circle_explosion", false, false, false);
//        _audio.play("explosion", false);
    }

    Explosion::~Explosion() = default;

    void Explosion::update(double t, float dt) {
        if (_animation->isFinished()) {
            _animation->start("ground_explosion", true, false, false);
        }

        if (_animation->isLoopFinished()) {
            _animation->setMirrorV(!_animation->getMirrorV());
//            setRotation(_rotation + 20);
        }

        Entity::update(t, dt);
    }
} // game