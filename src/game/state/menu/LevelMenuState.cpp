#include "LevelMenuState.h"
#include "game/state/world/LevelState.h"
#include "MainMenuState.h"

namespace game {
    LevelMenuState::LevelMenuState(Game &state_machine, std::stack<std::unique_ptr<IGameState>> &states)
            : MenuState(state_machine, states), _current_panel(0) {

        _level_amount = _state_machine.getLevelData().size();
        _panel_amount = _level_amount / 9;
        _remainder = _level_amount - (_panel_amount * 9);
        if (_remainder != 0) _panel_amount++;
    }

    void LevelMenuState::enter() {
        _menu_background = std::shared_ptr<engine::UIEntity>(new engine::UIEntity(
                {{0, 0}, {1, 1}, 0}
        ));
        _entities.push_back(_menu_background);

        _return_button = createMenuButton("return", {0, -0.75}, _menu_background);

        if (_panel_amount == 0) {
            std::shared_ptr<engine::ITextBoxComponent> text =
                    _state_machine.getViewComponentCreator()->createTextBox({1, 1}, constants::layer::ui_text, true,
                                                                            "PTSans-bold");
            text->setText("No levels!");
            text->setFontSize(0.25);

            std::shared_ptr<engine::UIEntity> text_entity = std::shared_ptr<engine::UIEntity>(new engine::UIEntity(
                    {{0, 0}, {1, 1}, 0},
                    {text,}
            ));

            _entities.push_back(text_entity);

        } else {
            createPanel();
        }

        MenuState::enter();
    }

    void LevelMenuState::graphicsUpdate(double t, float dt) {
        for (const auto &level_button_pair: _level_buttons) {
            if (level_button_pair.first->isActive()) {
                _state_machine.setCurrentLevelId(level_button_pair.second);
                set<LevelState>();
                return;
            }
        }

        if (_return_button->isActive()) {
            set<MainMenuState>();
        } else if (_left_arrow_button != nullptr && _left_arrow_button->isActive()) {
            _current_panel--;
            createPanel();
        } else if (_right_arrow_button != nullptr && _right_arrow_button->isActive()) {
            _current_panel++;
            createPanel();
        } else {
            IGameState::graphicsUpdate(t, dt);
        }
    }

    void LevelMenuState::handleInput(const InputEvent &input) {
        switch (input.type) {
            case InputEvent::Type::RETURN:
                set<MainMenuState>();
                break;

            default:
                MenuState::handleInput(input);
                break;
        }
    }

    void LevelMenuState::createPanel() {
        _panel = nullptr;

        _level_buttons.clear();

        _left_arrow_button = nullptr;
        _right_arrow_button = nullptr;

        _panel = std::shared_ptr<engine::UIEntity>(new engine::UIEntity(
                {{0, 0.2f}, {1, 1}, 0}
        ));
        _weak_entities.push_back(_panel);

        if (_current_panel != 0) {
            _left_arrow_button = createArrowButton({-1, 0}, true, _panel);
            _weak_entities.push_back(_left_arrow_button);
        }

        if (_current_panel != _panel_amount - 1) {
            _right_arrow_button = createArrowButton({1, 0}, false, _panel);
            _weak_entities.push_back(_right_arrow_button);
        }

        unsigned int current_level_id = _current_panel * 9;

        unsigned int panel_level_amount{9};
        if (_current_panel == _panel_amount - 1 && _remainder != 0) {
            panel_level_amount = _remainder;
        }

        float distance = 0.5f;
        engine::Vector2f button_start_position{-distance,
                                               distance};

        unsigned int current_panel_level_amount{0};
        for (int iy = 0; iy < 3; iy++) {
            for (int ix = 0; ix < 3; ix++) {
                engine::Vector2f button_position{
                        button_start_position.x + distance * static_cast<float>(ix),
                        button_start_position.y - distance * static_cast<float>(iy),
                };

                _level_buttons.emplace_back(
                        createLevelSelectButton(std::to_string(current_level_id + 1), button_position, _panel),
                        current_level_id
                );
                current_level_id++;
                current_panel_level_amount++;

                if (current_panel_level_amount == panel_level_amount) {
                    return;
                }
            }
        }
    }
} // game