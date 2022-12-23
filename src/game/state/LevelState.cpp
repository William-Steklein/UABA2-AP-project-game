#include "LevelState.h"
#include <engine/utils/file_io.h>

namespace game {
    LevelState::LevelState(Game &state_machine, std::stack<std::unique_ptr<IGameState>> &states)
            : WorldState(state_machine, states) {
        _level_data = state_machine.getCurrentLevelDataPoint();
    }

    void LevelState::enter() {
        loadLevelData();

        WorldState::enter();
    }

    void LevelState::loadLevelData() {
        for (const auto &entity_data: _level_data->entity_data) {
            switch (entity_data.id) {
                case 0:
                    createPlayer(entity_data.position);
                    break;

                case 1:
                    createWall(entity_data.position, entity_data.size);

                    break;

                default:

                    break;
            }
        }
    }
} // game