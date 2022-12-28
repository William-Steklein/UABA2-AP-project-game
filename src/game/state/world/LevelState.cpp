#include "LevelState.h"
#include "engine/utils/file_io.h"
#include "game/state/menu/LevelMenuState.h"
#include "game/state/menu/LevelFinishOverlayState.h"

namespace game {
    LevelState::LevelState(Game &state_machine, std::stack<std::unique_ptr<IGameState>> &states)
            : WorldState(state_machine, states) {

    }

    void LevelState::enter() {
        _level_data = _state_machine.getCurrentLevelDataPoint();
        loadLevelData();

        WorldState::enter();
    }

    void LevelState::reset() {
        _finish = nullptr;
        _level_data = nullptr;

        WorldState::reset();
    }

    void LevelState::loadLevelData() {
        createPlayer(_level_data->player.position, _level_data->player.size);

        createFinish(_level_data->finish.position, _level_data->finish.size);

        for (const auto& wall_data : _level_data->walls) {
            createWall(wall_data.position, wall_data.size, wall_data.sliding);
        }

        for (const auto& tile_data : _level_data->tiles) {
            unsigned int layer{0};
            switch (tile_data.type) {
                case 0:
                    layer = constants::layer::tile_bg;
                    break;

                case 1:
                    layer = constants::layer::tile_fg;
                    break;

                case 2:
                    layer = constants::layer::tile_prop;
                    break;

                default:
                    break;
            }

            createTile(tile_data.position, tile_data.size, layer, tile_data.sprite_id);
        }

        if (_finish == nullptr) {
            throw std::runtime_error("Loaded world has no finish");
        }
    }

    void LevelState::updateCollisions() {
        // finish
        if (_finish != nullptr) {
            if (_player->_physics_component->getHitBox()->collides(*_finish->getHitBox())) {
                push<LevelFinishOverlayState>();
                return;
            }
        }

        WorldState::updateCollisions();
    }

    void LevelState::createFinish(const engine::Vector2f &position, const engine::Vector2f &size) {
        _finish = std::make_shared<Finish>(Finish(
                {position, {1, 1}, 0},
                _state_machine.getViewComponentCreator()->createAnimatedSprite(size, constants::layer::finish, false,
                                                                               "blue_cube")
        ));

        _entities.push_back(_finish);
    }

    void LevelState::createDebugViewComponents() {
        // finish
        std::shared_ptr<engine::IShapeComponent> finish_rectangle =
                _state_machine.getViewComponentCreator()->createRectangle(
                        _finish->getHitBox()->getSize(), constants::layer::debug_finish_hit_box, false);
        finish_rectangle->setFillcolor({255, 153, 204, 200});
        finish_rectangle->setTransform(_finish->getTransform());
        finish_rectangle->setVisible(_debug_view_visibility);

        _debug_components.push_back(finish_rectangle);

        WorldState::createDebugViewComponents();
    }
} // game