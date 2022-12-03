#include "DebugState.h"
#include "game/state/OverlayMenuState.h"

namespace game {

    DebugState::DebugState() {

    }

    void DebugState::enter(Game &game) {
        game.getCamera()->reset();

        std::shared_ptr<engine::Entity> background = std::make_shared<engine::Entity>(engine::Entity(
                {{0, 0}, {2, 2}, 0},
                {
                    game.getViewComponentCreator()->createSprite({0.5, 0.5}, 0, false, "pr_background"),
                }
                ));

        _entities.insert(background);

        _player = std::make_shared<Player>(Player(
                {{0, 0}, {1, 1}, 0},
                game.getViewComponentCreator()->createAnimatedSprite({0.8f, 0.56f}, 1, false, "adventurer")
        ));

        _physics_entities.insert(_player);

        _walls.push_back(std::make_shared<Wall>(Wall(
                {{1, 0.5}, {1, 1}, 0},
                game.getViewComponentCreator()->createSprite({0.5f, 0.5f}, 2, false, "pr_ground")
        )));

        _physics_entities.insert(_walls.back());

        _walls.push_back(std::make_shared<Wall>(Wall(
                {{-1, 0.5}, {1, 1}, 0},
                game.getViewComponentCreator()->createSprite({0.5f, 0.5f}, 2, false, "cobble_stone")
        )));

        _physics_entities.insert(_walls.back());
    }

    void DebugState::reset(Game &game) {
        _player = nullptr;
        IGameState::reset(game);
    }

    void DebugState::update(Game &game, double t, float dt) {
        IGameState::update(game, t, dt);
    }

    void DebugState::physicsUpdate(Game &game, double t, float dt) {
        game.getCamera()->setPosition(_player->getPosition());

        IGameState::physicsUpdate(game, t, dt);
    }

    void DebugState::handleInput(Game &game, const InputEvent &input) {
        if (input.type == InputEvent::Type::RETURN && input.state_enter) {
            game.pushState(std::make_shared<OverlayMenuState>());
        }

        _player->handleInput(input);
    }
} // game