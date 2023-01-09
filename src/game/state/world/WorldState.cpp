#include "WorldState.h"
#include "game/state/menu/PauzeOverlayState.h"
#include "engine/Stopwatch/Stopwatch.h"
#include "game/entities/world/player/Player.h"
#include "game/entities/world/player/state/IPlayerState.h"

namespace game {

    WorldState::WorldState(Game &state_machine, std::stack<std::unique_ptr<IGameState>> &states)
            : IGameState(state_machine, states), _camera_limit(false), _camera_pos_y_lock(false),
              _debug_view_visibility(false) {

    }

    void WorldState::enter() {
        _debug_view_visibility = false;

        if (_player == nullptr) {
            throw std::runtime_error("Loaded world has no player");
        }

        if (_state_machine.showFramerate()) {
            _fps_counter_text = _state_machine.getViewComponentCreator()->createTextBox(
                    {0.5f, 0.25f}, constants::layer::ui_text, true, "PTSans-bold");
            _fps_counter_text->setFontSize(0.08f * constants::ui::scale_factor);

            _fps_counter = std::make_shared<engine::Entity>(engine::Entity(
                    {engine::Vector2f(-1.25, 0.9) * constants::ui::scale_factor, {1, 1}, 0},
                    {_fps_counter_text}
            ));
            _entities.push_back(_fps_counter);
        }

        createBackgroundBackground();

        createDebugViewComponents();

        updateFpsCounterText();

        if (!_camera_move_vector.empty()) {
            _state_machine.getCamera()->setPosition(_camera_start);
        } else {
            _state_machine.getCamera()->setPosition(_player->getPosition());
        }

        // graphics update after changing camera position
        graphicsUpdate(engine::Stopwatch::getInstance().getTime(),
                       engine::Stopwatch::getInstance().getDeltaTime());

        IGameState::enter();
    }

    void WorldState::reset() {
        _player = nullptr;

        _walls.clear();
        _slide_walls.clear();
        _tiles.clear();

        _debug_components.clear();

        _fps_counter_text = nullptr;
        _fps_counter = nullptr;

        _camera_limit = false;
        _camera_start.clear();
        _camera_move_vector.clear();
        _camera_pos_y_lock = false;

        IGameState::reset();
    }

    void WorldState::physicsUpdate(double t, float dt) {
        IGameState::physicsUpdate(t, dt);

        updateCollisions();
    }

    void WorldState::graphicsUpdate(double t, float dt) {
        controlCamera();

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

    void WorldState::createPlayer(const engine::Vector2f &position, const engine::Vector2f &size) {
        _player = std::shared_ptr<Player>(new Player(
                {position, {1, 1}, 0},
                _state_machine.getViewComponentCreator()->createAnimatedSprite(
                        size, constants::layer::player, false, "adventurer")
        ));

        _entities.push_back(_player);
    }

    void WorldState::controlCamera() {
        std::shared_ptr<engine::Camera> camera = _state_machine.getCamera();

        if (!_camera_move_vector.empty()) {
            camera->move(_camera_move_vector);
        } else {
            engine::Vector2f move_vector = _player->getPosition() - camera->getPosition();

            if (_camera_pos_y_lock && move_vector.y < 0) {
                move_vector.y = 0;
            }

            camera->move(move_vector);
        }

        if (_camera_limit) {
            camera->setPosition(engine::clamp(camera->getPosition(), _camera_min_limit, _camera_max_limit));
        }
    }

    void WorldState::createWall(const engine::Vector2f &position, const engine::Vector2f &size, bool slide) {
        _walls.push_back(std::make_shared<Wall>(Wall(
                {position, {1, 1}, 0},
                size
        )));

        if (slide) {
            _slide_walls.push_back(_walls.back());
        }
        _entities.push_back(_walls.back());
    }

    void WorldState::createTile(const engine::Vector2f &position, const engine::Vector2f &size,
                                unsigned int layer, const std::string &sprite_id) {
        _tiles.push_back(std::make_shared<Tile>(Tile(
                {position, {1, 1}, 0},
                _state_machine.getViewComponentCreator()->createSprite(size, layer, false, sprite_id)
        )));

        _entities.push_back(_tiles.back());
    }

    void WorldState::updateCollisions() {
        for (const auto &wall: _walls) {
            _player->_physics_component->handleCollision(*wall->getPhysicsComponent());

            _player->_standing_ray->collides(*wall->getPhysicsComponent()->getHitBox());
        }

        for (const auto &slide_wall: _slide_walls) {
            _player->_left_wall_slide_ray->collides(*slide_wall->getPhysicsComponent()->getHitBox());
            _player->_right_wall_slide_ray->collides(*slide_wall->getPhysicsComponent()->getHitBox());
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
        if (_fps_counter_text.get()) {
            _fps_counter_text->setText(std::to_string(engine::Stopwatch::getInstance().getAverageFps()));
        }
    }

    void WorldState::createBackgroundBackground() {
        _entities.push_back(std::make_shared<engine::Entity>(engine::Entity(
                {{-1.25, 0.25}, {1, 1}, 0},
                {_state_machine.getViewComponentCreator()->createSprite({2.5, 2.5}, constants::layer::bg_1, true,
                                                                        "bg-sky")}
        )));

        _entities.push_back(std::make_shared<engine::Entity>(engine::Entity(
                {{1.25, 0.25}, {1, 1}, 0},
                {_state_machine.getViewComponentCreator()->createSprite({2.5, 2.5}, constants::layer::bg_1, true,
                                                                        "bg-sky")})));

        _entities.push_back(std::make_shared<engine::Entity>(engine::Entity(
                {{0, 0}, {1, 1}, 0},
                {_state_machine.getViewComponentCreator()->createSprite({6, 6}, constants::layer::bg_2, true,
                                                                        "bg-mountains")}
        )));

        _entities.push_back(std::make_shared<engine::Entity>(engine::Entity(
                {{0, 0.25}, {1, 1}, 0},
                {_state_machine.getViewComponentCreator()->createSprite({6, 6}, constants::layer::bg_3, true,
                                                                        "bg-ruins")}
        )));

        _entities.push_back(std::make_shared<engine::Entity>(engine::Entity(
                {{2, 1.1}, {1, 1}, 0},
                {_state_machine.getViewComponentCreator()->createSprite({0.4, 0.4}, constants::layer::bg_4, true,
                                                                        "bg-sun")}
        )));
    }

} // game