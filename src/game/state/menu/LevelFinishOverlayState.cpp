#include "LevelFinishOverlayState.h"
#include "MainMenuState.h"
#include "LevelMenuState.h"

namespace game {
    LevelFinishOverlayState::LevelFinishOverlayState(Game &state_machine,
                                                     std::stack<std::unique_ptr<IGameState>> &states)
            : MenuState(state_machine, states), _last_level(_state_machine.isLastLevel()) {

    }

    void LevelFinishOverlayState::enter() {
        std::shared_ptr<engine::UIEntity> menu_background = createMenuBackground({0, 0});
        _entities.push_back(menu_background);

        if (!_last_level) {
            _next_level_button = createMenuButton("next level", constants::ui::menu::button_position_1, menu_background);
            _restart_button = createMenuButton("restart", constants::ui::menu::button_position_2, menu_background);

            _level_menu_button = createMenuButton("level menu", constants::ui::menu::button_position_3, menu_background);
            _main_menu_button = createMenuButton("main menu", constants::ui::menu::button_position_4, menu_background);
        } else {
            _next_level_button = nullptr;
            _restart_button = createMenuButton("restart", constants::ui::menu::button_position_1, menu_background);

            _level_menu_button = createMenuButton("level menu", constants::ui::menu::button_position_2, menu_background);
            _main_menu_button = createMenuButton("main menu", constants::ui::menu::button_position_3, menu_background);
        }

        State::enter();
    }

    void LevelFinishOverlayState::graphicsUpdate(double t, float dt) {
        if (_next_level_button != nullptr && _next_level_button->isActive()) {
            advanceCurrentLevel();
            return;
        } else if (_restart_button->isActive()) {
            popAndReset();
        } else if (_level_menu_button->isActive()) {
            popAndSet<LevelMenuState>();
        } else if (_main_menu_button->isActive()) {
            popAndSet<MainMenuState>();
        } else {
            IGameState::graphicsUpdate(t, dt);
        }
    }

    void LevelFinishOverlayState::handleInput(const InputEvent &input) {
        if (_next_level_button != nullptr && input.type == InputEvent::Type::ACCEPT) {
            advanceCurrentLevel();
            return;
        }

        MenuState::handleInput(input);
    }

    void LevelFinishOverlayState::advanceCurrentLevel() {
        _state_machine.advanceCurrentLevel();
        popAndReset();
    }
} // game