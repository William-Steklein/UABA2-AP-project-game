#ifndef GAME_ENGINE_LEVELSTATE_H
#define GAME_ENGINE_LEVELSTATE_H


#include "WorldState.h"

namespace game {

    class LevelState : public WorldState {
    public:
        LevelState(Game &game, std::string level_file_path);

        ~LevelState() override = default;

        void enter() override;

        void loadLevelFromFile();

    private:
        std::string _level_file_path;
    };

} // game

#endif //GAME_ENGINE_LEVELSTATE_H
