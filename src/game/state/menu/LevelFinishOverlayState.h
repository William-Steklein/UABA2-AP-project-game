#ifndef GAME_ENGINE_LEVELFINISHOVERLAYSTATE_H
#define GAME_ENGINE_LEVELFINISHOVERLAYSTATE_H

#include "game/state/menu/MenuState.h"

namespace game {

    class LevelFinishOverlayState : public MenuState {
    public:
        LevelFinishOverlayState(Game &state_machine, std::stack<std::unique_ptr<IGameState>> &states);

        void enter() override;

        void graphicsUpdate(double t, float dt) override;

        void handleInput(const game::InputEvent &input) override;

    private:
        bool _last_level;

        std::shared_ptr<Button> _next_level_button;
        std::shared_ptr<Button> _restart_button;
        std::shared_ptr<Button> _level_menu_button;
        std::shared_ptr<Button> _main_menu_button;

        void advanceCurrentLevel();
    };

} // game

#endif //GAME_ENGINE_LEVELFINISHOVERLAYSTATE_H
