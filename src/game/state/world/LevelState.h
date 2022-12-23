#ifndef GAME_ENGINE_LEVELSTATE_H
#define GAME_ENGINE_LEVELSTATE_H


#include "WorldState.h"

namespace game {

    class LevelState : public WorldState {
    public:
        LevelState(Game &state_machine, std::stack<std::unique_ptr<IGameState>> &states);

        ~LevelState() override = default;

        void enter() override;

        void loadLevelData();

    private:
        std::shared_ptr<LevelData> _level_data;
    };

} // game

#endif //GAME_ENGINE_LEVELSTATE_H
