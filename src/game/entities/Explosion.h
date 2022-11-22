#ifndef GAME_ENGINE_EXPLOSION_H
#define GAME_ENGINE_EXPLOSION_H


#include <Engine/entities/Entity.h>

namespace game {

    class Explosion : public engine::Entity {
    public:
        Explosion(std::shared_ptr<engine::IEntityView> view, std::shared_ptr<engine::EntityAnimation> animation);

        ~Explosion();

        void update(double t, float dt) override;
    };

} // game


#endif //GAME_ENGINE_EXPLOSION_H
