#ifndef GAME_ENGINE_MENUSTATE_H
#define GAME_ENGINE_MENUSTATE_H

#include <engine/entity/ui/UIEntity.h>

#include "game/state/IGameState.h"
#include "game/entities/ui/button/Button.h"
#include "game/entities/ui/button/ButtonState.h"

namespace game {

    class MenuState : public IGameState {
    public:
        using IGameState::IGameState;

        void handleInput(const game::InputEvent &input) override;

        std::shared_ptr<engine::UIEntity>
        createMenuBackground(const engine::Vector2f &position,
                             const std::shared_ptr<engine::UIEntity> &parent = nullptr,
                             const engine::Vector2f &size = {1.f, 1.5f});

        std::shared_ptr<Button> createMenuButton(const std::string &text, const engine::Vector2f &position,
                                                 const std::shared_ptr<engine::UIEntity> &parent = nullptr,
                                                 const engine::Vector2f &size = {0.5f, 0.25f},
                                                 float font_size = 0.085f);

        std::shared_ptr<Button> createLevelSelectButton(const std::string &text, const engine::Vector2f &position,
                                     const std::shared_ptr<engine::UIEntity> &parent = nullptr,
                                     const engine::Vector2f &size = {0.3f, 0.3f},
                                     float font_size = 0.085f);

        std::shared_ptr<Button> createArrowButton(const engine::Vector2f &position,
                                                  bool left = false,
                                                  const std::shared_ptr<engine::UIEntity> &parent = nullptr,
                                                  const engine::Vector2f &size = {0.3f, 0.3f});

    protected:
        std::vector<std::weak_ptr<Button>> _buttons;
    };

} // game

#endif //GAME_ENGINE_MENUSTATE_H
