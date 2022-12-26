#include "PauzeOverlayState.h"
#include "MainMenuState.h"

namespace game {
    void PauzeOverlayState::enter() {
        std::shared_ptr<engine::UIEntity> menu_background = createMenuBackground({0, 0});
        _entities.push_back(menu_background);

        _resume_button = createMenuButton("resume", {0, 0.51}, menu_background);
        _restart_button = createMenuButton("restart", {0, 0.175}, menu_background);
        _main_menu_button = createMenuButton("main menu", {0, -0.175}, menu_background);

        MenuState::enter();
    }

    void PauzeOverlayState::graphicsUpdate(double t, float dt) {
        if (_resume_button->isActive()) {
            pop();
        } else if (_restart_button->isActive()) {
            popAndReset();
        } else if (_main_menu_button->isActive()) {
            popAndSet<MainMenuState>();
        } else {
            IGameState::graphicsUpdate(t, dt);
        }
    }

    void PauzeOverlayState::handleInput(const InputEvent &input) {
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