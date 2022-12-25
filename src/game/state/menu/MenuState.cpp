#include "MenuState.h"

namespace game {
    void MenuState::handleInput(const InputEvent &input) {
        switch (input.type) {
            case InputEvent::Type::MOUSEMOVED:
            case InputEvent::Type::MOUSECLICK:
                for (auto button_it = _buttons.begin(); button_it != _buttons.end();) {
                    if ((*button_it).expired()) {
                        button_it = _buttons.erase(button_it);
                    } else {
                        button_it->lock()->handleInput(input);

                        button_it++;
                    }
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

        std::shared_ptr<engine::UIEntity> menu_background = std::shared_ptr<engine::UIEntity>(new engine::UIEntity(
                {position, {1, 1}, 0},
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

        std::shared_ptr<Button> button = std::shared_ptr<Button>(new Button(
                {position, {1, 1}, 0},
                size,
                _state_machine.getMousePosition(),
                _state_machine.getViewComponentCreator()->createAnimatedSprite(
                        size, button_layer, true, "menu_button"),
                {button_text}
        ));

        if (parent != nullptr) {
            parent->addChild(button, parent);
        }

        _buttons.push_back(button);

        return button;
    }

    std::shared_ptr<Button>
    MenuState::createLevelSelectButton(const std::string &text, const engine::Vector2f &position,
                                       const std::shared_ptr<engine::UIEntity> &parent,
                                       const engine::Vector2f &size,
                                       float font_size) {
        unsigned int button_layer = 9;
        unsigned int text_layer = 10;

        std::shared_ptr<engine::ITextBoxComponent> button_text =
                _state_machine.getViewComponentCreator()->createTextBox(size, text_layer, true, "PTSans-bold");
        button_text->setText(text);
        button_text->setFontSize(font_size);

        std::shared_ptr<Button> button = std::shared_ptr<Button>(new Button(
                {position, {1, 1}, 0},
                size,
                _state_machine.getMousePosition(),
                _state_machine.getViewComponentCreator()->createAnimatedSprite(
                        size, button_layer, true, "level_menu_button"),
                {button_text}
        ));

        if (parent != nullptr) {
            parent->addChild(button, parent);
        }

        _buttons.push_back(button);

        return button;
    }

    std::shared_ptr<Button> MenuState::createArrowButton(const engine::Vector2f &position, bool left,
                                                         const std::shared_ptr<engine::UIEntity> &parent,
                                                         const engine::Vector2f &size) {
        unsigned int button_layer = 9;

        std::shared_ptr<Button> button = std::shared_ptr<Button>(new Button(
                {position, {1, 1}, 0},
                size,
                _state_machine.getMousePosition(),
                _state_machine.getViewComponentCreator()->createAnimatedSprite(
                        size, button_layer, true, "arrow_button")
        ));

        // set direction
        button->_animated_sprite->setMirrorH(left);

        if (parent != nullptr) {
            parent->addChild(button, parent);
        }

        _buttons.push_back(button);

        return button;
    }
} // game