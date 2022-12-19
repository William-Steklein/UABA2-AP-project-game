#ifndef GAME_ENGINE_LEVELSTATE_H
#define GAME_ENGINE_LEVELSTATE_H


#include "WorldState.h"

namespace game {

    class LevelState : public WorldState {
    public:
        LevelState(Game &game, std::shared_ptr<LevelData> level_data);

        ~LevelState() override = default;

        void enter() override;

        void loadLevelData();

    private:
        std::shared_ptr<LevelData> _level_data;
    };

} // game

#endif //GAME_ENGINE_LEVELSTATE_H
