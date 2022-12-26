#include "WorldState.h"
#include "game/state/menu/PauzeOverlayState.h"
#include "engine/Stopwatch.h"
#include "game/entities/world/player/Player.h"
#include "game/entities/world/player/state/IPlayerState.h"
#include "game/state/menu/LevelMenuState.h"

namespace game {

    WorldState::WorldState(Game &state_machine, std::stack<std::unique_ptr<IGameState>> &states)
            : IGameState(state_machine, states),
              _debug_view_visibility(false) {

    }

    void WorldState::enter() {
        _debug_view_visibility = false;

        if (_player == nullptr) {
            throw std::runtime_error("Loaded world has no player");
        }

        _fps_counter_text = _state_machine.getViewComponentCreator()->createTextBox(
                {0.5f, 0.25f}, 5, true, "PTSans-bold");
        _fps_counter_text->setFontSize(0.08f);

        _fps_counter = std::make_shared<engine::Entity>(engine::Entity(
                {{-1.25, 0.9}, {1, 1}, 0},
                {_fps_counter_text}
        ));
        _entities.push_back(_fps_counter);

        createDebugViewComponents();

        updateFpsCounterText();

        cameraFollowPlayer();
        // graphics update after changing camera position
        graphicsUpdate(engine::Stopwatch::getInstance().getTime(),
                       engine::Stopwatch::getInstance().getDeltaTime());

        IGameState::enter();
    }

    void WorldState::reset() {
        _player = nullptr;

        _walls.clear();

        _debug_components.clear();

        _fps_counter_text = nullptr;
        _fps_counter = nullptr;

        IGameState::reset();
    }

    void WorldState::physicsUpdate(double t, float dt) {
        IGameState::physicsUpdate(t, dt);

        updateCollisions();
    }

    void WorldState::graphicsUpdate(double t, float dt) {
        cameraFollowPlayer();

        updateFpsCounterText();

        IGameState::graphicsUpdate(t, dt);
        updateDebugViewComponents(t, dt);
    }

    void WorldState::handleInput(const InputEvent &input) {
        switch (input.type) {
            case InputEvent::Type::RETURN:
                if (input.state == InputEvent::State::ENTERED) {
                    push<PauzeOverlayState>();
                }

                break;

            case InputEvent::Type::DEBUGVIEW:
                if (input.state == InputEvent::State::ENTERED) {
                    toggleDebugViewVisibility();
                }

                break;

            default:
                _player->handleInput(input);

                break;
        }
    }

    void WorldState::createPlayer(const engine::Vector2f &position) {
        _player = std::shared_ptr<Player>(new Player(
                {position, {1, 1}, 0},
                _state_machine.getViewComponentCreator()->createAnimatedSprite(
                        constants::player::view_size, constants::layer::player, false, "adventurer")
        ));

        _entities.push_back(_player);
    }

    void WorldState::cameraFollowPlayer() {
        _state_machine.getCamera()->setPosition(_player->getPosition());
    }

    void WorldState::createWall(const engine::Vector2f &position, const engine::Vector2f &size) {
        _walls.push_back(std::make_shared<Wall>(Wall(
                {position, {1, 1}, 0},
                _state_machine.getViewComponentCreator()->createSprite(size, constants::layer::tile, false,
                                                                       "pr_ground_2")
        )));

        _entities.push_back(_walls.back());
    }

    void WorldState::updateCollisions() {
        for (const auto &wall: _walls) {
            _player->_physics_component->handleCollision(*wall->getPhysicsComponent());

            _player->_standing_ray->collides(*wall->getPhysicsComponent()->getHitBox());
            _player->_left_wall_slide_ray->collides(*wall->getPhysicsComponent()->getHitBox());
            _player->_right_wall_slide_ray->collides(*wall->getPhysicsComponent()->getHitBox());
        }
    }

    void WorldState::createDebugViewComponents() {
        // player
        std::shared_ptr<engine::IShapeComponent> player_rectangle =
                _state_machine.getViewComponentCreator()->createRectangle(
                        _player->_physics_component->getHitBox()->getSize(), constants::layer::debug_player_hit_box,
                        false);
        player_rectangle->setFillcolor({255, 0, 255, 100});
        player_rectangle->setRelativeTransform(_player->_physics_component->getHitBox()->getRelativeTransform());
        player_rectangle->setTransform(_player->getTransform());
        player_rectangle->setVisible(_debug_view_visibility);

        _debug_components.push_back(player_rectangle);

        std::shared_ptr<engine::ILineComponent> player_standing_line =
                _state_machine.getViewComponentCreator()->createLine(constants::layer::debug_player_standing_ray, false,
                                                                     _player->_standing_ray->getOrigin(),
                                                                     _player->_standing_ray->getEnd());
        player_standing_line->setFillcolor({255, 255, 128});
        player_standing_line->setTransform(_player->getTransform());
        player_standing_line->setVisible(_debug_view_visibility);

        _debug_components.push_back(player_standing_line);

        std::shared_ptr<engine::ILineComponent> player_left_wall_slide_line =
                _state_machine.getViewComponentCreator()->createLine(constants::layer::debug_player_wall_slide_ray,
                                                                     false,
                                                                     _player->_left_wall_slide_ray->getOrigin(),
                                                                     _player->_left_wall_slide_ray->getEnd());
        player_left_wall_slide_line->setFillcolor({192, 255, 140});
        player_left_wall_slide_line->setTransform(_player->getTransform());
        player_left_wall_slide_line->setVisible(_debug_view_visibility);

        _debug_components.push_back(player_left_wall_slide_line);

        std::shared_ptr<engine::ILineComponent> player_right_wall_slide_line =
                _state_machine.getViewComponentCreator()->createLine(constants::layer::debug_player_wall_slide_ray,
                                                                     false,
                                                                     _player->_right_wall_slide_ray->getOrigin(),
                                                                     _player->_right_wall_slide_ray->getEnd());
        player_right_wall_slide_line->setFillcolor({192, 255, 140});
        player_right_wall_slide_line->setTransform(_player->getTransform());
        player_right_wall_slide_line->setVisible(_debug_view_visibility);

        _debug_components.push_back(player_right_wall_slide_line);

        // walls
        for (const auto &wall: _walls) {
            std::shared_ptr<engine::IShapeComponent> wall_rectangle =
                    _state_machine.getViewComponentCreator()->createRectangle(
                            wall->getPhysicsComponent()->getHitBox()->getSize(), constants::layer::debug_wall_hit_box,
                            false);
            wall_rectangle->setFillcolor({0, 255, 255, 200});
            wall_rectangle->setTransform(wall->getTransform());
            wall_rectangle->setVisible(_debug_view_visibility);

            _debug_components.push_back(wall_rectangle);
        }

        updateDebugViewComponents(0, 0);
    }

    void WorldState::updateDebugViewComponents(double t, float dt) {
        for (const auto &component: _debug_components) {
            component->update(t, dt);
        }
    }

    void WorldState::toggleDebugViewVisibility() {
        _debug_view_visibility = !_debug_view_visibility;

        for (auto &component: _debug_components) {
            component->setVisible(_debug_view_visibility);
        }
    }

    void WorldState::updateFpsCounterText() {
        _fps_counter_text->setText(std::to_string(engine::Stopwatch::getInstance().getAverageFps()));
    }

} // game