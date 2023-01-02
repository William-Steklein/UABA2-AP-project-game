#include "LevelState.h"
#include "engine/utils/file_io.h"
#include "game/state/menu/LevelMenuState.h"
#include "game/state/menu/LevelFinishOverlayState.h"

namespace game {
    LevelState::LevelState(Game &state_machine, std::stack<std::unique_ptr<IGameState>> &states)
            : WorldState(state_machine, states), _finished(false) {

    }

    void LevelState::enter() {
        _level_data = _state_machine.getCurrentLevelDataPoint();
        loadLevelData();

        WorldState::enter();
    }

    void LevelState::reset() {
        _finish = nullptr;
        _finished = false;
        _level_data = nullptr;

        WorldState::reset();
    }

    void LevelState::graphicsUpdate(double t, float dt) {
        WorldState::graphicsUpdate(t, dt);

        if (_finished) {
            push<LevelFinishOverlayState>();
            return;
        }
    }

    void LevelState::physicsUpdate(double t, float dt) {
        WorldState::physicsUpdate(t, dt);

        if (!_state_machine.getCamera()->isInView(_player->getPosition())) {
            return reset();
        }
    }

    void LevelState::loadLevelData() {
        // camera limit
        if (!_level_data->limit.empty()) {
            _camera_limit = true;

            engine::Vector2f camera_limit = _level_data->limit -
                                            engine::Vector2f(_state_machine.getCamera()->getWidth(),
                                                             _state_machine.getCamera()->getHeight());

            _camera_min_limit = {_level_data->origin.x - camera_limit.x / 2,
                                 _level_data->origin.y - camera_limit.y / 2};
            _camera_max_limit = {_level_data->origin.x + camera_limit.x / 2,
                                 _level_data->origin.y + camera_limit.y / 2};

            _level_min_limit = {_level_data->origin.x - _level_data->limit.x / 2,
                                 _level_data->origin.y - _level_data->limit.y / 2};
            _level_max_limit = {_level_data->origin.x + _level_data->limit.x / 2,
                                 _level_data->origin.y + _level_data->limit.y / 2};
        }

        // camera move
        if (_level_data->camera_move_time != 0) {
            _camera_start = _level_data->camera_start;

            float move_amount = _level_data->camera_move_time / engine::constants::physics_delta_time;

            _camera_move_vector = (_level_data->camera_end - _level_data->camera_start) / move_amount;

            _state_machine.getCamera()->setPosition(_camera_start);
        }

        createPlayer(_level_data->player.position, _level_data->player.size);

        createFinish(_level_data->finish.position, _level_data->finish.size);

        for (const auto &wall_data: _level_data->walls) {
            createWall(wall_data.position, wall_data.size, wall_data.sliding);
        }

        for (const auto &tile_data: _level_data->tiles) {
            unsigned int layer{0};
            switch (tile_data.type) {
                case 0:
                    layer = constants::layer::tile_bg;
                    break;

                case 1:
                    layer = constants::layer::tile_prop;
                    break;

                case 2:
                    layer = constants::layer::tile_fg;
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
                _finished = true;
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