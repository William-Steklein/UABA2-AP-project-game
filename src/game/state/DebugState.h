#ifndef GAME_ENGINE_DEBUGSTATE_H
#define GAME_ENGINE_DEBUGSTATE_H


#include "game/state/IGameState.h"
#include "game/Game.h"
#include "game/entities/player/Player.h"
#include "game/entities/player/PlayerState.h"

namespace game {

    class DebugState : public IGameState {
    public:
        DebugState();

        ~DebugState() override = default;

        void enter(game::Game &game) override;

        std::shared_ptr<IGameState> update(game::Game &game, double t, float dt) override;

        std::shared_ptr<IGameState> physicsUpdate(game::Game &game, double t, float dt) override;

        std::shared_ptr<IGameState> handleInput(game::Game &game, const game::InputEvent &input) override;

    private:
        std::shared_ptr<Player> _player;
    };

} // game


#endif //GAME_ENGINE_DEBUGSTATE_H