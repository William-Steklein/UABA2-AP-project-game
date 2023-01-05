#include "MainMenuState.h"
#include "game/state/menu/LevelMenuState.h"

namespace game {
    void MainMenuState::enter() {
        _state_machine.getCamera()->reset();

        std::shared_ptr<engine::UIEntity> menu_background = createMenuBackground({0, 0});
        _entities.push_back(menu_background);

        _play_button = createMenuButton("play", {0, 0.51}, menu_background);
        _quit_button = createMenuButton("quit", {0, 0.175}, menu_background);

        MenuState::enter();
    }

    void MainMenuState::graphicsUpdate(double t, float dt) {
        if (_play_button->isActive()) {
            set<LevelMenuState>();
//        } else if (_debug_button->isActive()) {
//            set<DebugState>();
        } else if (_quit_button->isActive()) {
            _state_machine.quit();
        } else {
            MenuState::graphicsUpdate(t, dt);
        }
    }

} // game