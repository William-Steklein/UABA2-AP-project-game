#include "DebugState.h"
#include "game/state/MenuState.h"

namespace game {

    DebugState::DebugState() {

    }

    void DebugState::enter(Game &game) {
        _player = std::make_shared<Player>(Player(
                {{0, 0}, {1, 1}, 0},
                std::make_shared<IdleState>(),
                game.getViewComponentCreator()->createAnimatedSprite({0.8f, 0.56f}, 0, "adventurer")
        ));

        _physics_entities.insert(_player);
    }

    void DebugState::update(Game &game, double t, float dt) {
        IGameState::update(game, t, dt);
    }

    void DebugState::physicsUpdate(Game &game, double t, float dt) {
        IGameState::physicsUpdate(game, t, dt);
    }

    std::shared_ptr<IGameState> DebugState::handleInput(Game &game, const InputEvent &input) {
        if (input.type == InputEvent::Type::RETURN) {
            return std::make_shared<MenuState>();
        }

        _player->handleInput(input);

        return nullptr;
    }
} // game