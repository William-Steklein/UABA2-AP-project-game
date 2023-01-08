#ifndef GAME_ENGINE_PAUZEOVERLAYSTATE_H
#define GAME_ENGINE_PAUZEOVERLAYSTATE_H


#include "game/state/menu/MenuState.h"

namespace game {

    class PauzeOverlayState : public MenuState {
    public:
        using MenuState::MenuState;

        void enter() override;

        void graphicsUpdate(double t, float dt) override;

        void handleInput(const game::InputEvent &input) override;

    private:
        std::shared_ptr<Button> _resume_button;
        std::shared_ptr<Button> _restart_button;
        std::shared_ptr<Button> _level_menu_button;
        std::shared_ptr<Button> _main_menu_button;
    };

} // game

#endif //GAME_ENGINE_PAUZEOVERLAYSTATE_H
