#include "DebugState.h"
#include "game/state/MenuState.h"

namespace game {

    DebugState::DebugState() {

    }

    void DebugState::enter(Game &game) {
        game.getCamera()->reset();

        std::shared_ptr<engine::UIEntity> menu_background = std::make_shared<engine::UIEntity>(engine::UIEntity(
                {{0, 0}, {1, 1}, 0},
                {game.getViewComponentCreator()->createSprite({1.f, 1.5f}, 0, true, "menu"),}
        ));
        _entities.insert(menu_background);

        _player = std::make_shared<Player>(Player(
                {{0, 0}, {1, 1}, 0},
                std::make_shared<IdleState>(),
                game.getViewComponentCreator()->createAnimatedSprite({0.8f, 0.56f}, 1, false, "adventurer")
        ));

        _physics_entities.insert(_player);
    }

    std::shared_ptr<IGameState> DebugState::update(Game &game, double t, float dt) {
        return IGameState::update(game, t, dt);
    }

    std::shared_ptr<IGameState> DebugState::physicsUpdate(Game &game, double t, float dt) {
        game.getCamera()->move({0.005f, 0});

        return IGameState::physicsUpdate(game, t, dt);
    }

    std::shared_ptr<IGameState> DebugState::handleInput(Game &game, const InputEvent &input) {
        if (input.type == InputEvent::Type::RETURN) {
            return std::make_shared<MenuState>();
        }

        _player->handleInput(input);

        return nullptr;
    }
} // game