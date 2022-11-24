#ifndef GAME_ENGINE_EXPLOSION_H
#define GAME_ENGINE_EXPLOSION_H


#include <engine/entity/Entity.h>

namespace game {

    class Explosion : public engine::Entity {
    public:
        Explosion(const engine::Transform &transform,
                  std::shared_ptr<engine::AnimationComponent> animation = nullptr,
                  std::shared_ptr<engine::IAudioComponent> audio = nullptr);

        ~Explosion() = default;

        void update(double t, float dt) override;
    };

} // game


#endif //GAME_ENGINE_EXPLOSION_H
