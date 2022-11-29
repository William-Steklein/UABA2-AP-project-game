#ifndef GAME_ENGINE_MENUSTATE_H
#define GAME_ENGINE_MENUSTATE_H


#include <engine/entity/ui/UIEntity.h>
#include "game/entities/widgets/UIButton.h"

#include "game/Game.h"
#include "game/state/IGameState.h"

namespace game {

    class MenuState : public IGameState {
    public:
        MenuState();

        ~MenuState() override = default;

        void enter(game::Game &game) override;

        std::shared_ptr<IGameState> update(game::Game &game, double t, float dt) override;

        std::shared_ptr<IGameState> handleInput(game::Game &game, const game::InputEvent &input) override;

    private:
        std::set<std::shared_ptr<UIButton>> _buttons;

    };

} // game

#endif //GAME_ENGINE_MENUSTATE_H
