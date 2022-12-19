#include "MenuState.h"
#include "game/state/DebugState.h"
#include "LevelState.h"

namespace game {
    MenuState::MenuState(Game &game)
            : IGameState(game), _selected_button_index(0), _keyboard_focus(false) {

    }

    void MenuState::enter() {
        _game.getCamera()->reset();

        unsigned int background_layer = 0;
        unsigned int button_layer = 1;
        unsigned int text_layer = 2;

        std::shared_ptr<engine::UIEntity> menu_background = std::make_shared<engine::UIEntity>(engine::UIEntity(
                {{0, 0}, {1, 1}, 0},
                {_game.getViewComponentCreator()->createSprite({1.f, 1.5f}, background_layer, true, "menu"),}
        ));
        _entities.insert(menu_background);

        engine::Vector2f button_size = {0.5f, 0.25f};
        float button_font_size = 0.085f;

        std::shared_ptr<engine::ITextBoxComponent> play_button_text =
                _game.getViewComponentCreator()->createTextBox(button_size, text_layer, true, "PTSans-bold");
        play_button_text->setText("play");
        play_button_text->setFontSize(button_font_size);

        _play_button = std::make_shared<UIButton>(UIButton(
                {{0, 0.51}, {1, 1}, 0},
                button_size,
                _game.getMousePosition(),
                _game.getViewComponentCreator()->createAnimatedSprite(button_size, button_layer, true, "button_anim"),
                {play_button_text}
        ));

        menu_background->addChild(_play_button, menu_background);
        _buttons.push_back(_play_button);


        std::shared_ptr<engine::ITextBoxComponent> debug_button_text =
                _game.getViewComponentCreator()->createTextBox(button_size, text_layer, true, "PTSans-bold");
        debug_button_text->setText("debug mode");
        debug_button_text->setFontSize(button_font_size);

        _debug_button = std::make_shared<UIButton>(UIButton(
                {{0, 0.175}, {1, 1}, 0},
                button_size,
                _game.getMousePosition(),
                _game.getViewComponentCreator()->createAnimatedSprite(button_size, button_layer, true, "button_anim"),
                {debug_button_text}
        ));

        menu_background->addChild(_debug_button, menu_background);
        _buttons.push_back(_debug_button);


        std::shared_ptr<engine::ITextBoxComponent> quit_button_text =
                _game.getViewComponentCreator()->createTextBox(button_size, text_layer, true, "PTSans-bold");
        quit_button_text->setText("quit");
        quit_button_text->setFontSize(button_font_size);

        _quit_button = std::make_shared<UIButton>(UIButton(
                {{0, -0.175}, {1, 1}, 0},
                button_size,
                _game.getMousePosition(),
                _game.getViewComponentCreator()->createAnimatedSprite(button_size, button_layer, true, "button_anim"),
                {quit_button_text}
        ));

        menu_background->addChild(_quit_button, menu_background);
        _buttons.push_back(_quit_button);
    }

    void MenuState::graphicsUpdate(double t, float dt) {
        if (_play_button->isActive()) {
//            _play_button->reset();
//            if (_keyboard_focus) {
//                _buttons[_selected_button_index]->setKeyboardActive();
//            }
            _game.setState(std::make_shared<LevelState>(_game, _game.getLevelData()[0]));
        } else if (_debug_button->isActive()) {
            _game.setState(std::make_shared<DebugState>(_game));
        } else if (_quit_button->isActive()) {
            _game.quit();
        }

        IGameState::graphicsUpdate(t, dt);
    }

    void MenuState::handleInput(const InputEvent &input) {
        switch (input.type) {
            case InputEvent::Type::UP:
                if (input.state == InputEvent::State::EXITED) {
                    if (!_keyboard_focus) {
                        toggleKeyboardFocus(true);
                    } else {
                        selectNextButton(true);
                    }
                }

                break;

            case InputEvent::Type::DOWN:
                if (input.state == InputEvent::State::EXITED) {
                    if (!_keyboard_focus) {
                        toggleKeyboardFocus(true);
                    } else {
                        selectNextButton(false);
                    }
                }

                break;

            case InputEvent::Type::ACCEPT:
                checkButtons();
                _buttons[_selected_button_index]->handleInput(input);
                break;

            case InputEvent::Type::MOUSEMOVED:
            case InputEvent::Type::MOUSECLICK:
                toggleKeyboardFocus(false);

                for (const auto &button: {_play_button, _debug_button, _quit_button}) {
                    button->handleInput(input);
                }
                break;

            default:
                break;
        }
    }

    void MenuState::checkButtons() {
        if (_buttons.empty()) {
            throw std::runtime_error("Button selection menu has no buttons");
        }
    }

    void MenuState::toggleKeyboardFocus(bool keyboard_focus) {
        checkButtons();

        if (_keyboard_focus == keyboard_focus) {
            return;
        }

        _keyboard_focus = keyboard_focus;

        if (keyboard_focus) {
            _buttons[_selected_button_index]->setKeyboardActive();
        } else {
            _buttons[_selected_button_index]->setKeyboardInactive();
        }

        _selected_button_index = 0;
    }

    void MenuState::selectNextButton(bool up) {
        _buttons[_selected_button_index]->setKeyboardInactive();
        if (up) {
            _selected_button_index -= 1;
            if (_selected_button_index < 0) {
                _selected_button_index = _buttons.size() - 1;
            }
        } else {
            _selected_button_index += 1;
            if (_selected_button_index >= _buttons.size()) {
                _selected_button_index = 0;
            }
        }
        _buttons[_selected_button_index]->setKeyboardActive();
    }
} // game