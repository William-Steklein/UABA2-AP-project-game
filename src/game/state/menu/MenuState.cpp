#include "MenuState.h"
#include "game/constants/constants.h"

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
        std::shared_ptr<engine::UIEntity> menu_background = std::shared_ptr<engine::UIEntity>(new engine::UIEntity(
                {position, {1, 1}, 0},
                {_state_machine.getViewComponentCreator()->createSprite(size, constants::layer::ui_menu, true, "menu"),}
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
        std::shared_ptr<engine::ITextBoxComponent> button_text =
                _state_machine.getViewComponentCreator()->createTextBox(size, constants::layer::ui_text, true,
                                                                        "PTSans-bold");
        button_text->setText(text);
        button_text->setFontSize(font_size);

        std::shared_ptr<Button> button = std::shared_ptr<Button>(new Button(
                {position, {1, 1}, 0},
                size,
                _state_machine.getMousePosition(),
                _state_machine.getViewComponentCreator()->createAnimatedSprite(
                        size, constants::layer::ui_button, true, "menu_button"),
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
        std::shared_ptr<engine::ITextBoxComponent> button_text =
                _state_machine.getViewComponentCreator()->createTextBox(size, constants::layer::ui_text, true,
                                                                        "PTSans-bold");
        button_text->setText(text);
        button_text->setFontSize(font_size);

        std::shared_ptr<Button> button = std::shared_ptr<Button>(new Button(
                {position, {1, 1}, 0},
                size,
                _state_machine.getMousePosition(),
                _state_machine.getViewComponentCreator()->createAnimatedSprite(
                        size, constants::layer::ui_button, true, "level_menu_button"),
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
        std::shared_ptr<Button> button = std::shared_ptr<Button>(new Button(
                {position, {1, 1}, 0},
                size,
                _state_machine.getMousePosition(),
                _state_machine.getViewComponentCreator()->createAnimatedSprite(
                        size, constants::layer::ui_button, true, "arrow_button")
        ));

        // set direction
        button->_animated_sprite->setMirrorH(left);

        if (parent != nullptr) {
            parent->addChild(button, parent);
        }

        _buttons.push_back(button);

        return button;
    }

    void MenuState::createBackground() {
        _entities.push_back(std::make_shared<engine::Entity>(engine::Entity(
                {{-1.5, 0}, {1, 1}, 0},
                {_state_machine.getViewComponentCreator()->createSprite({3, 3}, constants::layer::bg_1, true,
                                                                        "bg-sky")}
        )));

        _entities.push_back(std::make_shared<engine::Entity>(engine::Entity(
                {{1.5, 0}, {1, 1}, 0},
                {_state_machine.getViewComponentCreator()->createSprite({3, 3}, constants::layer::bg_1, true,
                                                                        "bg-sky")}
        )));

        _entities.push_back(std::make_shared<engine::Entity>(engine::Entity(
                {{2, 1.1}, {1, 1}, 0},
                {_state_machine.getViewComponentCreator()->createSprite({0.4, 0.4}, constants::layer::bg_4, true,
                                                                        "bg-sun")}
        )));
    }
} // game