#ifndef GAME_ENGINE_LEVELMENUSTATE_H
#define GAME_ENGINE_LEVELMENUSTATE_H

#include "game/state/menu/MenuState.h"

namespace game {

    class LevelMenuState : public MenuState {
    public:
        LevelMenuState(Game &state_machine, std::stack<std::unique_ptr<IGameState>> &states);

        void enter() override;

        void graphicsUpdate(double t, float dt) override;

        void handleInput(const game::InputEvent &input) override;

    private:
        std::shared_ptr<engine::UIEntity> _menu_background;

        std::shared_ptr<Button> _return_button;
        std::shared_ptr<Button> _left_arrow_button;
        std::shared_ptr<Button> _right_arrow_button;

        std::vector<std::shared_ptr<Button>> _level_buttons;

        unsigned int _current_panel;
        unsigned int _level_amount;
        unsigned int _panel_amount;
        unsigned int _remainder;

        void createPanel(unsigned int panel_nr);
    };

} // game

#endif //GAME_ENGINE_LEVELMENUSTATE_H
