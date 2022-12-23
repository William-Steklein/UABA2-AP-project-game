#include "OverlayMenuState.h"
#include "game/state/MenuState.h"

namespace game {
    OverlayMenuState::OverlayMenuState(Game &game) : IGameState(game) {

    }

    void OverlayMenuState::enter() {
        unsigned int background_layer = 8;
        unsigned int button_layer = 9;
        unsigned int text_layer = 10;

        std::shared_ptr<engine::UIEntity> menu_background = std::make_shared<engine::UIEntity>(engine::UIEntity(
                {{0, 0}, {1, 1}, 0},
                {_game.getViewComponentCreator()->createSprite({1.f, 1.5f}, background_layer, true, "menu"),}
        ));
        _entities.insert(menu_background);

        engine::Vector2f button_size = {0.5f, 0.25f};
        float button_font_size = 0.085f;

        std::shared_ptr<engine::ITextBoxComponent> play_button_text =
                _game.getViewComponentCreator()->createTextBox(button_size, text_layer, true, "PTSans-bold");
        play_button_text->setText("resume");
        play_button_text->setFontSize(button_font_size);

        _resume_button = std::make_shared<Button>(Button(
                {{0, 0.51}, {1, 1}, 0},
                button_size,
                _game.getMousePosition(),
                _game.getViewComponentCreator()->createAnimatedSprite(button_size, button_layer, true, "button_anim"),
                {play_button_text}
        ));

        menu_background->addChild(_resume_button, menu_background);


        std::shared_ptr<engine::ITextBoxComponent> debug_button_text =
                _game.getViewComponentCreator()->createTextBox(button_size, text_layer, true, "PTSans-bold");
        debug_button_text->setText("restart");
        debug_button_text->setFontSize(button_font_size);

        _restart_button = std::make_shared<Button>(Button(
                {{0, 0.175}, {1, 1}, 0},
                button_size,
                _game.getMousePosition(),
                _game.getViewComponentCreator()->createAnimatedSprite(button_size, button_layer, true, "button_anim"),
                {debug_button_text}
        ));

        menu_background->addChild(_restart_button, menu_background);


        std::shared_ptr<engine::ITextBoxComponent> quit_button_text =
                _game.getViewComponentCreator()->createTextBox(button_size, text_layer, true, "PTSans-bold");
        quit_button_text->setText("main menu");
        quit_button_text->setFontSize(button_font_size);

        _main_menu_button = std::make_shared<Button>(Button(
                {{0, -0.175}, {1, 1}, 0},
                button_size,
                _game.getMousePosition(),
                _game.getViewComponentCreator()->createAnimatedSprite(button_size, button_layer, true, "button_anim"),
                {quit_button_text}
        ));

        menu_background->addChild(_main_menu_button, menu_background);
    }

    void OverlayMenuState::graphicsUpdate(double t, float dt) {
        if (_resume_button->isActive()) {
            _game.popState();
        } else if (_restart_button->isActive()) {
            _game.popAndResetState();
        } else if (_main_menu_button->isActive()) {
            _game.popAndSetState(std::make_shared<MenuState>(_game));
        }

        IGameState::graphicsUpdate(t, dt);
    }

    void OverlayMenuState::handleInput(const InputEvent &input) {
        switch (input.type) {
            case InputEvent::Type::RETURN:
                if (input.state == InputEvent::State::ENTERED) {
                    _game.popState();
                }

            case InputEvent::Type::MOUSEMOVED:
            case InputEvent::Type::MOUSECLICK:
                for (const auto &button: {_resume_button, _restart_button, _main_menu_button}) {
                    button->handleInput(input);
                }
                break;

            default:
                break;
        }
    }
} // game