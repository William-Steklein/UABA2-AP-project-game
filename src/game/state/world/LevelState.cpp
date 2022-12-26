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
        for (const auto &entity_data: _level_data->entity_data) {
            switch (entity_data.id) {
                case 0:
                    createPlayer(entity_data.position);
                    break;

                case 1:
                    createWall(entity_data.position, entity_data.size);

                    break;

                case 2:
                    createFinish(entity_data.position, entity_data.size);

                    break;

                default:

                    break;
            }
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