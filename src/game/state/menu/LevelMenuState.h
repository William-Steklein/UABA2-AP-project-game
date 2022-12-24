#ifndef GAME_ENGINE_LEVELMENUSTATE_H
#define GAME_ENGINE_LEVELMENUSTATE_H

#include "game/state/menu/MenuState.h"

namespace game {

    class LevelMenuState : public MenuState {
        using MenuState::MenuState;

        void enter() override;

        void graphicsUpdate(double t, float dt);
    };

} // game

#endif //GAME_ENGINE_LEVELMENUSTATE_H
