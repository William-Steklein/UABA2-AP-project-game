#include "MenuState.h"
#include "game/state/DebugState.h"

namespace game {
    MenuState::MenuState() {

    }

    void MenuState::enter(Game &game) {
        std::shared_ptr<engine::UIEntity> menu_background = std::make_shared<engine::UIEntity>(engine::UIEntity(
                {{0, 0}, {1, 1}, 0},
                {
                        game.getViewComponentCreator()->createSprite({1.f, 1.5f}, 0, "menu"),
                }
        ));
        _entities.insert(menu_background);

        engine::Vector2f button_size = {0.5f, 0.25f};

        std::shared_ptr<engine::ITextBoxComponent> debug_button_text =
                game.getViewComponentCreator()->createTextBox(button_size * 0.5f, 1, "PTSans-regular");
        debug_button_text->setText("debug");

        std::shared_ptr<UIButton> debug_button = std::make_shared<UIButton>(UIButton(
                {{0, 0.5f}, {1, 1}, 0},
                button_size,
                game.getMousePosition(),
                game.getViewComponentCreator()->createAnimatedSprite(button_size, 0, "button_anim"),
                {
                        debug_button_text,
                }
        ));

        menu_background->addChild(debug_button, menu_background);
        _buttons.insert(debug_button);
    }

    std::shared_ptr<IGameState> MenuState::update(Game &game, double t, float dt) {
        for (const auto &button: _buttons) {
            if (button->isActive()) {
                return std::make_shared<DebugState>();
            }
        }

        return IGameState::update(game, t, dt);
    }

    std::shared_ptr<IGameState> MenuState::handleInput(Game &game, const InputEvent &input) {
        switch (input.type) {
            case InputEvent::Type::ACCEPT:
                return std::make_shared<DebugState>();

            case InputEvent::Type::MOUSEMOVED:
            case InputEvent::Type::MOUSECLICK:
                for (const auto &button: _buttons) {
                    button->handleInput(input);
                }
                break;

            default:
                break;
        }

        if (input.type == InputEvent::Type::ACCEPT) {
            return std::make_shared<DebugState>();
        }

        return nullptr;
    }
} // game