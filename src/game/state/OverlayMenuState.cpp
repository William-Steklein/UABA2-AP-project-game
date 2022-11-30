#include "OverlayMenuState.h"
#include "game/state/MenuState.h"

void game::OverlayMenuState::enter(game::Game &game) {
    unsigned int background_layer = 8;
    unsigned int button_layer = 9;
    unsigned int text_layer = 10;

    std::shared_ptr<engine::UIEntity> menu_background = std::make_shared<engine::UIEntity>(engine::UIEntity(
            {{0, 0}, {1, 1}, 0},
            {game.getViewComponentCreator()->createSprite({1.f, 1.5f}, background_layer, true, "menu"),}
    ));
    _entities.insert(menu_background);

    engine::Vector2f button_size = {0.5f, 0.25f};
    float button_font_size = 0.085f;

    std::shared_ptr<engine::ITextBoxComponent> play_button_text =
            game.getViewComponentCreator()->createTextBox(button_size, text_layer, true, "PTSans-bold");
    play_button_text->setText("resume");
    play_button_text->setFontSize(button_font_size);

    _resume_button = std::make_shared<UIButton>(UIButton(
            {{0, 0.51}, {1, 1}, 0},
            button_size,
            game.getMousePosition(),
            game.getViewComponentCreator()->createAnimatedSprite(button_size, button_layer, true, "button_anim"),
            {play_button_text}
    ));

    menu_background->addChild(_resume_button, menu_background);


    std::shared_ptr<engine::ITextBoxComponent> debug_button_text =
            game.getViewComponentCreator()->createTextBox(button_size, text_layer, true, "PTSans-bold");
    debug_button_text->setText("restart");
    debug_button_text->setFontSize(button_font_size);

    _restart_button = std::make_shared<UIButton>(UIButton(
            {{0, 0.175}, {1, 1}, 0},
            button_size,
            game.getMousePosition(),
            game.getViewComponentCreator()->createAnimatedSprite(button_size, button_layer, true, "button_anim"),
            {debug_button_text}
    ));

    menu_background->addChild(_restart_button, menu_background);


    std::shared_ptr<engine::ITextBoxComponent> quit_button_text =
            game.getViewComponentCreator()->createTextBox(button_size, text_layer, true, "PTSans-bold");
    quit_button_text->setText("main menu");
    quit_button_text->setFontSize(button_font_size);

    _main_menu_button = std::make_shared<UIButton>(UIButton(
            {{0, -0.175}, {1, 1}, 0},
            button_size,
            game.getMousePosition(),
            game.getViewComponentCreator()->createAnimatedSprite(button_size, button_layer, true, "button_anim"),
            {quit_button_text}
    ));

    menu_background->addChild(_main_menu_button, menu_background);
}

void game::OverlayMenuState::update(game::Game &game, double t, float dt) {
    if (_resume_button->isActive()) {
        game.popState();
    } else if (_restart_button->isActive()) {
        game.popAndResetState();
    } else if (_main_menu_button->isActive()) {
        game.popAndSetState(std::make_shared<MenuState>());
    }

    IGameState::update(game, t, dt);
}

void game::OverlayMenuState::handleInput(game::Game &game, const game::InputEvent &input) {
    switch (input.type) {
        case InputEvent::Type::RETURN:
            if (input.state_enter) {
                game.popState();
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