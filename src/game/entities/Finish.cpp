#include "Finish.h"

namespace game {
    Finish::Finish(engine::Transform transform, std::shared_ptr<engine::IAnimatedSpriteComponent> animated_sprite)
            : engine::Entity(std::move(transform)),
            _animated_sprite(std::move(animated_sprite)),
            _activated(false) {
        addComponent(_animated_sprite, false);

        _hit_box = std::make_shared<engine::HitBox>(_animated_sprite->getSize() * 0.75f);
        addComponent(_hit_box, true);

        _animated_sprite->start("default", true);
    }

    bool Finish::isActivated() const {
        return _activated;
    }

    void Finish::setActivated(bool activated) {
        _activated = activated;
    }

    const std::shared_ptr<engine::HitBox> &Finish::getHitBox() const {
        return _hit_box;
    }
} // game