#include "MenuState.h"
#include "game/state/DebugState.h"

namespace game {
    MenuState::MenuState() {

    }

    void MenuState::enter(Game &game) {
        std::shared_ptr<engine::UIEntity> menu_background = std::make_shared<engine::UIEntity>(engine::UIEntity(
                {{0, 0}, {1, 1}, 0},
                {
                        game.getViewComponentCreator()->createSprite({1.f, 1.5f}, 0, "menu")
                }
        ));
        _entities.insert(menu_background);

        std::shared_ptr<engine::UIEntity> debug_button = std::make_shared<engine::UIEntity>(engine::UIEntity(
                {{0, 0.5f}, {1, 1}, 0},
                {
                        game.getViewComponentCreator()->createSprite({0.5f, 0.25f}, 0, "button")
                }
        ));

        menu_background->addChild(debug_button, menu_background);
    }

    void MenuState::update(Game &game, double t, float dt) {
        IGameState::update(game, t, dt);
    }

    std::shared_ptr<IGameState> MenuState::handleInput(Game &game, const InputEvent &input) {
        if (input.type == InputEvent::Type::ACCEPT) {
            return std::make_shared<DebugState>();
        }

        return nullptr;
    }
} // game