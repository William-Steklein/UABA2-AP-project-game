#include "LevelMenuState.h"
#include "game/state/world/LevelState.h"
#include "MainMenuState.h"

namespace game {
    LevelMenuState::LevelMenuState(Game &state_machine, std::stack<std::unique_ptr<IGameState>> &states)
            : MenuState(state_machine, states), _current_panel(0) {

//        _level_nr = _state_machine.getLevelData().size();
        _level_amount = 9;

        _panel_amount = _level_amount / 9;
        _remainder = _level_amount - (_panel_amount * 9);
    }

    void LevelMenuState::enter() {
        _menu_background = std::unique_ptr<engine::UIEntity>(new engine::UIEntity(
                {{0, 0}, {1, 1}, 0}
        ));
        _entities.insert(_menu_background);

        _return_button = createMenuButton("return", {0, -0.75}, _menu_background);

        _left_arrow_button = createArrowButton({-1, 0}, true, _menu_background);
        _right_arrow_button = createArrowButton({1, 0}, false, _menu_background);

        createPanel(_current_panel);

        MenuState::enter();
    }

    void LevelMenuState::graphicsUpdate(double t, float dt) {
        if (_return_button->isActive()) {
            set<MainMenuState>();
        } else if (_level_buttons[0]->isActive()) {
            set<LevelState>();
        } else {
            IGameState::graphicsUpdate(t, dt);
        }
    }

    void LevelMenuState::handleInput(const InputEvent &input) {
        switch (input.type) {
            case InputEvent::Type::RETURN:
                set<MainMenuState>();
                break;

            default:
                MenuState::handleInput(input);
                break;
        }
    }

    void LevelMenuState::createPanel(unsigned int panel_nr) {
        engine::Vector2f panel_position{0, 0.2f};
        float distance = 0.5f;
        engine::Vector2f panel_start_position{panel_position.x - distance,
                                              panel_position.y + distance};

        unsigned int current_level_nr = 1;

        for (int iy = 0; iy < 3; iy++) {
            for (int ix = 0; ix < 3; ix++) {
                engine::Vector2f button_position{
                        panel_start_position.x + distance * static_cast<float>(ix),
                        panel_start_position.y - distance * static_cast<float>(iy),
                };

                _level_buttons.push_back(createLevelSelectButton(
                        std::to_string(current_level_nr), button_position, _menu_background));
                current_level_nr++;
            }
        }

//        for (int i = 0; _remainder == 0 ? i < _panel_amount : i <= _panel_amount; i++) {
//
//        }
    }
} // game