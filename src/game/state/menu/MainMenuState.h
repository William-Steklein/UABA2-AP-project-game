#ifndef GAME_ENGINE_MAINMENUSTATE_H
#define GAME_ENGINE_MAINMENUSTATE_H

#include "game/state/menu/MenuState.h"

namespace game {

    class MainMenuState : public MenuState {
    public:
        using MenuState::MenuState;

        void enter() override;

        void graphicsUpdate(double t, float dt) override;

    private:
        std::shared_ptr<Button> _play_button;
        std::shared_ptr<Button> _quit_button;
    };

} // game

#endif //GAME_ENGINE_MAINMENUSTATE_H
