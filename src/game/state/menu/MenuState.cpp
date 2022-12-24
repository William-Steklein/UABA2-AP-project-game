#include "MenuState.h"

namespace game {
    void MenuState::handleInput(const InputEvent &input) {
        switch (input.type) {
            case InputEvent::Type::MOUSEMOVED:
            case InputEvent::Type::MOUSECLICK:
                for (const auto &button: _buttons) {
                    button->handleInput(input);
                }
                break;

            default:
                IGameState::handleInput(input);
        }
    }

    std::shared_ptr<engine::UIEntity>
    MenuState::createMenuBackground(const engine::Vector2f &position,
                                    const std::shared_ptr<engine::UIEntity> &parent,
                                    const engine::Vector2f &size) {
        unsigned int background_layer = 8;

        std::shared_ptr<engine::UIEntity> menu_background = std::unique_ptr<engine::UIEntity>(new engine::UIEntity(
                {{0, 0}, {1, 1}, 0},
                {_state_machine.getViewComponentCreator()->createSprite(size, background_layer, true, "menu"),}
        ));

        if (parent != nullptr) {
            parent->addChild(menu_background, parent);
        }

        return menu_background;
    }

    std::shared_ptr<Button>
    MenuState::createMenuButton(const std::string &text, const engine::Vector2f &position,
                                const std::shared_ptr<engine::UIEntity> &parent,
                                const engine::Vector2f &size,
                                float font_size) {
        unsigned int button_layer = 9;
        unsigned int text_layer = 10;

        std::shared_ptr<engine::ITextBoxComponent> button_text =
                _state_machine.getViewComponentCreator()->createTextBox(size, text_layer, true, "PTSans-bold");
        button_text->setText(text);
        button_text->setFontSize(font_size);

        std::shared_ptr<Button> button = std::unique_ptr<Button>(new Button(
                {position, {1, 1}, 0},
                size,
                _state_machine.getMousePosition(),
                _state_machine.getViewComponentCreator()->createAnimatedSprite(
                        size, button_layer, true, "button_anim"),
                {button_text}
        ));

        if (parent != nullptr) {
            parent->addChild(button, parent);
        }

        _buttons.push_back(button);

        return button;
    }

    void MenuState::createLevelSelectButton() {

    }
} // game