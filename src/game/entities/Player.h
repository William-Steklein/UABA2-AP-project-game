#ifndef GAME_ENGINE_PLAYER_H
#define GAME_ENGINE_PLAYER_H


#include <utility>

#include <engine/entity/Entity.h>

namespace game {

    class Player : public engine::Entity {
    public:
        Player(const engine::Transform &transform, std::shared_ptr<engine::IViewComponent> view = nullptr,
               std::shared_ptr<engine::AnimationComponent> animation = nullptr,
               std::shared_ptr<engine::IAudioComponent> audio = nullptr);

        ~Player() = default;

        void update(double t, float dt) override;

    private:

    };

} // game

#endif //GAME_ENGINE_PLAYER_H
