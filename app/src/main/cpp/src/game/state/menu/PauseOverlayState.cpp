#include "PauseOverlayState.h"
#include "MainMenuState.h"
#include "LevelMenuState.h"

namespace game {
    void PauseOverlayState::enter() {
        std::shared_ptr<engine::UIEntity> menu_background = createMenuBackground({0, 0});
        _entities.push_back(menu_background);

        _resume_button = createMenuButton("resume", constants::ui::menu::button_position_1, menu_background);
        _restart_button = createMenuButton("restart", constants::ui::menu::button_position_2, menu_background);
        _level_menu_button = createMenuButton("level menu", constants::ui::menu::button_position_3, menu_background);
        _main_menu_button = createMenuButton("main menu", constants::ui::menu::button_position_4, menu_background);

        MenuState::enter();
    }

    void PauseOverlayState::graphicsUpdate(double t, float dt) {
        if (_resume_button->isActive()) {
            pop();
        } else if (_restart_button->isActive()) {
            popAndReset();
        } else if (_main_menu_button->isActive()) {
            popAndSet<MainMenuState>();
        } else if (_level_menu_button->isActive()) {
            popAndSet<LevelMenuState>();
        } else {
            IGameState::graphicsUpdate(t, dt);
        }
    }

    void PauseOverlayState::handleInput(const InputEvent &input) {
        switch (input.type) {
            case InputEvent::Type::RETURN:
                if (input.state == InputEvent::State::ENTERED) {
                    pop();
                }

            default:
                MenuState::handleInput(input);
        }
    }
} // game