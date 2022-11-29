#include "MenuState.h"

namespace game {
    MenuState::MenuState() {

    }

    void MenuState::enter(Game &game) {
        _player = std::make_shared<Player>(Player(
                {{0, 0}, {1, 1}, 0},
                std::make_shared<IdleState>(),
                game.getViewComponentCreator()->createAnimatedSprite({0.8f, 0.56f}, 0, "adventurer")
        ));

        _physics_entities.insert(_player);
    }

    void MenuState::update(Game &game, double t, float dt) {
        IGameState::update(game, t, dt);
    }

    void MenuState::physicsUpdate(game::Game &game, double t, float dt) {
        IGameState::physicsUpdate(game, t, dt);
    }

    std::shared_ptr<IGameState> MenuState::handleInput(Game &game, const InputEvent &input) {
        _player->handleInput(input);

        return nullptr;
    }
} // game