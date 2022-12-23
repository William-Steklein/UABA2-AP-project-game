#ifndef GAME_ENGINE_MENUSTATE_H
#define GAME_ENGINE_MENUSTATE_H


#include <engine/entity/ui/UIEntity.h>

#include "game/entities/ui-widgets/button/Button.h"
#include "game/state/IGameState.h"

namespace game {

    class MenuState : public IGameState {
    public:
        MenuState(Game &game);

        ~MenuState() override = default;

        void enter() override;

        void graphicsUpdate(double t, float dt) override;

        void handleInput(const game::InputEvent &input) override;

    private:
        std::vector<std::shared_ptr<Button>> _buttons;

        std::shared_ptr<Button> _play_button;
        std::shared_ptr<Button> _debug_button;
        std::shared_ptr<Button> _quit_button;
    };

} // game

#endif //GAME_ENGINE_MENUSTATE_H
