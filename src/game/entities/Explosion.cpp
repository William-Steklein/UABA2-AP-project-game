#include "Explosion.h"

namespace game {
    Explosion::Explosion(std::shared_ptr<engine::IEntityView> view, std::shared_ptr<engine::EntityAnimation> animation)
            : engine::Entity(std::move(view), std::move(animation)) {
        // animation name, loop, mirror_h, mirror_v
        _animation->start("circle_explosion", false, false, false);
//        _audio.play("explosion", false);
    }

    Explosion::~Explosion() = default;

    void Explosion::update(double t, float dt) {
        if (_animation->isFinished()) {
//            LOGDEBUG(true);
            _animation->start("ground_explosion", true, false, false);
        }

        if (_animation->isLoopFinished()) {
            _animation->setMirrorV(!_animation->getMirrorV());
            LOGDEBUG("loop finished");
        }

        Entity::update(t, dt);
    }
} // game