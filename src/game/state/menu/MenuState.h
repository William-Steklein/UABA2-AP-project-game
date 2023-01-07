#ifndef GAME_ENGINE_MENUSTATE_H
#define GAME_ENGINE_MENUSTATE_H

#include <engine/entity/ui/UIEntity.h>

#include "game/state/IGameState.h"
#include "game/entities/ui/button/Button.h"
#include "game/entities/ui/button/ButtonState.h"
#include "game/constants/constants.h"

namespace game {

    class MenuState : public IGameState {
    public:
        using IGameState::IGameState;

        void handleInput(const game::InputEvent &input) override;

        std::shared_ptr<engine::UIEntity>
        createMenuBackground(const engine::Vector2f &position = constants::ui::menu::position,
                             const std::shared_ptr<engine::UIEntity> &parent = nullptr,
                             const engine::Vector2f &size = constants::ui::menu::size);

        std::shared_ptr<Button> createMenuButton(const std::string &text, const engine::Vector2f &position,
                                                 const std::shared_ptr<engine::UIEntity> &parent = nullptr,
                                                 const engine::Vector2f &size = constants::ui::menu::button_size,
                                                 float font_size = constants::ui::menu::font_size);

        std::shared_ptr<Button> createLevelSelectButton(const std::string &text, const engine::Vector2f &position,
                                                        const std::shared_ptr<engine::UIEntity> &parent = nullptr,
                                                        const engine::Vector2f &size =
                                                        constants::ui::level_menu::level_select_button_size,
                                                        float font_size = constants::ui::menu::font_size);

        std::shared_ptr<Button> createArrowButton(const engine::Vector2f &position,
                                                  bool left = false,
                                                  const std::shared_ptr<engine::UIEntity> &parent = nullptr,
                                                  const engine::Vector2f &size =
                                                  constants::ui::level_menu::arrow_button_size);

        void createBackground();

    protected:
        std::vector<std::weak_ptr<Button>> _buttons;
    };

} // game

#endif //GAME_ENGINE_MENUSTATE_H
