#ifndef GAME_ENGINE_DEBUGSTATE_H
#define GAME_ENGINE_DEBUGSTATE_H


#include "game/state/IGameState.h"
#include "game/entities/player/Player.h"
#include "game/entities/Wall.h"

namespace game {

    class DebugState : public IGameState {
    public:
        DebugState();

        ~DebugState() override = default;

        void enter(game::Game &game) override;

        void reset(Game &game) override;

        void update(game::Game &game, double t, float dt) override;

        void physicsUpdate(game::Game &game, double t, float dt) override;

        void handleInput(game::Game &game, const game::InputEvent &input) override;

    private:
        std::shared_ptr<Player> _player;
        std::vector<std::shared_ptr<Wall>> _walls;
    };

} // game


#endif //GAME_ENGINE_DEBUGSTATE_H
