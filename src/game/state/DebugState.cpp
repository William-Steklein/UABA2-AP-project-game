#include "DebugState.h"
#include "game/state/OverlayMenuState.h"

namespace game {

    DebugState::DebugState() {

    }

    void DebugState::enter(Game &game) {
        game.getCamera()->reset();

        _player = std::make_shared<Player>(Player(
                {{0, 0}, {1, 1}, 0},
                std::make_shared<IdleState>(),
                game.getViewComponentCreator()->createAnimatedSprite({0.8f, 0.56f}, 1, false, "adventurer")
        ));

        _physics_entities.insert(_player);
    }

    void DebugState::reset(Game &game) {
        _player = nullptr;
        IGameState::reset(game);
    }

    void DebugState::update(Game &game, double t, float dt) {
        IGameState::update(game, t, dt);
    }

    void DebugState::physicsUpdate(Game &game, double t, float dt) {
        IGameState::physicsUpdate(game, t, dt);
    }

    void DebugState::handleInput(Game &game, const InputEvent &input) {
        if (input.type == InputEvent::Type::RETURN && input.state_enter) {
            game.pushState(std::make_shared<OverlayMenuState>());
        }

        _player->handleInput(input);
    }
} // game