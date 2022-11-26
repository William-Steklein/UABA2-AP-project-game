#ifndef GAME_ENGINE_EXPLOSION_H
#define GAME_ENGINE_EXPLOSION_H


#include <engine/entity/Entity.h>
#include "engine/entity/components/view/sprite/ISpriteComponent.h"
#include "engine/entity/components/view/sprite/IAnimatedSpriteComponent.h"
#include <engine/entity/components/audio/IAudioComponent.h>
#include "engine/entity/components/view/text/ITextBoxComponent.h"

namespace game {

    class Explosion : public engine::Entity {
    public:
        Explosion(const engine::Transform &transform,
                  std::shared_ptr<engine::IAnimatedSpriteComponent> animation = nullptr,
                  std::shared_ptr<engine::IAudioComponent> audio = nullptr);

        ~Explosion() = default;

        void update(double t, float dt) override;

    private:
        std::shared_ptr<engine::IAnimatedSpriteComponent> _animation;
        std::shared_ptr<engine::IAudioComponent> _audio;
    };

} // game


#endif //GAME_ENGINE_EXPLOSION_H
