#ifndef GAME_ENGINE_MENUSTATE_H
#define GAME_ENGINE_MENUSTATE_H


#include "game/state/IGameState.h"
#include "game/Game.h"
#include "game/entities/player/Player.h"
#include "game/entities/player/PlayerState.h"

namespace game {

    class MenuState : public IGameState {
    public:
        MenuState();

        ~MenuState() override = default;

        void enter(game::Game &game) override;

        void update(game::Game &game, double t, float dt) override;

        void physicsUpdate(game::Game &game, double t, float dt) override;

        std::shared_ptr<IGameState> handleInput(game::Game &game, const game::InputEvent &input) override;

    private:
        std::shared_ptr<Player> _player;
    };

} // game

#endif //GAME_ENGINE_MENUSTATE_H
