#ifndef GAME_ENGINE_FINISH_H
#define GAME_ENGINE_FINISH_H

#include <engine/entity/Entity.h>
#include <engine/entity/components/view/sprite/IAnimatedSpriteComponent.h>
#include <engine/entity/components/physics/PhysicsComponent.h>

namespace game {

    class Finish : public engine::Entity {
    public:
        Finish(engine::Transform transform,
               std::shared_ptr<engine::IAnimatedSpriteComponent> animated_sprite);

        bool isActivated() const;

        void setActivated(bool activated);

        const std::shared_ptr<engine::HitBox> &getHitBox() const;

    private:
        bool _activated;

        std::shared_ptr<engine::IAnimatedSpriteComponent> _animated_sprite;
        std::shared_ptr<engine::HitBox> _hit_box;
    };

} // game

#endif //GAME_ENGINE_FINISH_H
