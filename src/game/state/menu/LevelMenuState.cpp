#include "LevelMenuState.h"
#include "game/state/world/LevelState.h"

namespace game {
    void LevelMenuState::enter() {


        MenuState::enter();
    }

    void LevelMenuState::graphicsUpdate(double t, float dt) {

        IGameState::graphicsUpdate(t, dt);
    }
} // game