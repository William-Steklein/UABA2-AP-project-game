#include "LevelState.h"
#include <engine/utils/file_io.h>

#include <utility>
#include <algorithm>

namespace game {
    LevelState::LevelState(Game &game, std::shared_ptr<LevelData> level_data)
            : WorldState(game), _level_data(std::move(level_data)) {

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