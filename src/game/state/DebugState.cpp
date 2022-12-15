#include "DebugState.h"
#include "game/state/OverlayMenuState.h"
#include "game/constants/constants.h"

#include <engine/Stopwatch.h>

namespace game {

    DebugState::DebugState(Game &game) : IGameState(game), _debug_view_visibility(false) {

    }

    void DebugState::enter() {
        _game.getCamera()->reset();

        generateBackground({0, 0}, {20, 20}, {0.5, 0.5});

        _player = std::make_shared<Player>(Player(
                {{0, 1}, {1, 1}, 0},
                _game.getViewComponentCreator()->createAnimatedSprite(constants::player::view_size, 1, false,
                                                                      "adventurer")
        ));

        _entities.insert(_player);

        createWall({-0.5, 0.25}, {0.25, 0.25});
        createWall({-1, 0.5}, {0.25, 0.25});

        createWall({2, 2}, {0.25, 4});
        createWall({2.75, 2}, {0.25, 4});


        createWall({0, -0.5}, {10, 0.25});

        createDebugViewComponents();


        _fps_counter_text = _game.getViewComponentCreator()->createTextBox(
                {0.5f, 0.25f}, 5, true, "PTSans-bold");
        _fps_counter_text->setFontSize(0.08f);

        _fps_counter = std::make_shared<engine::Entity>(engine::Entity(
                {{-1.25, 0.9}, {1, 1}, 0},
                {_fps_counter_text}
        ));
        _entities.insert(_fps_counter);

        updateFpsCounterText();
    }

    void DebugState::resume() {

    }

    void DebugState::reset() {
        _player = nullptr;

        _walls.clear();

        _debug_components.clear();

        _fps_counter_text = nullptr;
        _fps_counter = nullptr;

        IGameState::reset();
    }

    void DebugState::physicsUpdate(double t, float dt) {
        IGameState::physicsUpdate(t, dt);

        updateCollisions();
    }

    void DebugState::graphicsUpdate(double t, float dt) {
        _game.getCamera()->setPosition(_player->getPosition());

        updateFpsCounterText();

        IGameState::graphicsUpdate(t, dt);

        for (const auto &component: _debug_components) {
            component->update(t, dt);
        }
    }

    void DebugState::handleInput(const InputEvent &input) {
        switch (input.type) {
            case InputEvent::Type::RETURN:
                if (input.state == InputEvent::State::ENTERED) {
                    _game.pushState(std::make_shared<OverlayMenuState>(_game));
                }

                break;

            case InputEvent::Type::DEBUGVIEW:
                if (input.state == InputEvent::State::ENTERED) {
                    toggleDebugViewVisibility();
                }

                break;

            default:
                break;
        }

        _player->handleInput(input);
    }

    void DebugState::generateBackground(const engine::Vector2f &position,
                                        const engine::Vector2f &size, const engine::Vector2f &entity_size) {
        engine::Vector2f total_size = {std::ceil(size.x / entity_size.x) * entity_size.x,
                                       std::ceil(size.y / entity_size.y) * entity_size.y};
        engine::Vector2f origin = (position - total_size / 2) + entity_size / 2;

        int x_tile_count = std::ceil(size.x / entity_size.x);
        int y_tile_count = std::ceil(size.y / entity_size.y);
        for (int y_count = 0; y_count < y_tile_count; y_count++) {
            for (int x_count = 0; x_count < x_tile_count; x_count++) {
                engine::Vector2f entity_position = {origin.x + static_cast<float>(x_count) * entity_size.x,
                                                    origin.y + static_cast<float>(y_count) * entity_size.y};

                std::shared_ptr<engine::Entity> background = std::make_shared<engine::Entity>(engine::Entity(
                        {entity_position, {1, 1}, 0},
                        {_game.getViewComponentCreator()->createSprite(entity_size, 0, false, "pr_background"),}
                ));

                _entities.insert(background);
            }
        }
    }

    void DebugState::createWall(const engine::Vector2f &position, const engine::Vector2f &size) {
        unsigned int layer = 2;

        _walls.push_back(std::make_shared<Wall>(Wall(
                {position, {1, 1}, 0},
                _game.getViewComponentCreator()->createSprite(size, layer, false, "pr_ground_2")
        )));

        _entities.insert(_walls.back());
    }

    void DebugState::updateCollisions() {
        for (const auto &wall: _walls) {
            _player->_physics_component->handleCollision(*wall->getPhysicsComponent());

            _player->_standing_ray->collides(*wall->getPhysicsComponent()->getHitBox());
            _player->_left_wall_slide_ray->collides(*wall->getPhysicsComponent()->getHitBox());
            _player->_right_wall_slide_ray->collides(*wall->getPhysicsComponent()->getHitBox());
        }
    }

    void DebugState::createDebugViewComponents() {
        // player
        std::shared_ptr<engine::IShapeComponent> player_rectangle = _game.getViewComponentCreator()->createRectangle(
                _player->_physics_component->getHitBox()->getSize(), 2, false);
        player_rectangle->setFillcolor({255, 0, 255, 100});
        player_rectangle->setRelativeTransform(_player->_physics_component->getHitBox()->getRelativeTransform());
        player_rectangle->setTransform(_player->getTransform());
        player_rectangle->setVisible(_debug_view_visibility);

        _debug_components.push_back(player_rectangle);

        std::shared_ptr<engine::ILineComponent> player_standing_line =
                _game.getViewComponentCreator()->createLine(5, false, _player->_standing_ray->getOrigin(),
                                                            _player->_standing_ray->getEnd());
        player_standing_line->setFillcolor({255, 255, 128});
        player_standing_line->setTransform(_player->getTransform());
        player_standing_line->setVisible(_debug_view_visibility);

        _debug_components.push_back(player_standing_line);

        std::shared_ptr<engine::ILineComponent> player_left_wall_slide_line =
                _game.getViewComponentCreator()->createLine(5, false, _player->_left_wall_slide_ray->getOrigin(),
                                                            _player->_left_wall_slide_ray->getEnd());
        player_left_wall_slide_line->setFillcolor({192, 255, 140});
        player_left_wall_slide_line->setTransform(_player->getTransform());
        player_left_wall_slide_line->setVisible(_debug_view_visibility);

        _debug_components.push_back(player_left_wall_slide_line);

        std::shared_ptr<engine::ILineComponent> player_right_wall_slide_line =
                _game.getViewComponentCreator()->createLine(5, false, _player->_right_wall_slide_ray->getOrigin(),
                                                            _player->_right_wall_slide_ray->getEnd());
        player_right_wall_slide_line->setFillcolor({192, 255, 140});
        player_right_wall_slide_line->setTransform(_player->getTransform());
        player_right_wall_slide_line->setVisible(_debug_view_visibility);

        _debug_components.push_back(player_right_wall_slide_line);

        // walls
        for (const auto &wall: _walls) {
            std::shared_ptr<engine::IShapeComponent> wall_rectangle = _game.getViewComponentCreator()->createRectangle(
                    wall->getPhysicsComponent()->getHitBox()->getSize(), 2, false);
            wall_rectangle->setFillcolor({0, 255, 255, 200});
            wall_rectangle->setTransform(wall->getTransform());
            wall_rectangle->setVisible(_debug_view_visibility);

            _debug_components.push_back(wall_rectangle);
        }
    }

    void DebugState::toggleDebugViewVisibility() {
        _debug_view_visibility = !_debug_view_visibility;

        for (auto &component: _debug_components) {
            component->setVisible(_debug_view_visibility);
        }
    }

    void DebugState::updateFpsCounterText() {
        _fps_counter_text->setText(std::to_string(engine::Stopwatch::getInstance().getAverageFps()));
    }
} // game