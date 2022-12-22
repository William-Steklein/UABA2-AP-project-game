#ifndef GAME_ENGINE_OVERLAYMENUSTATE_H
#define GAME_ENGINE_OVERLAYMENUSTATE_H


#include <engine/entity/ui/UIEntity.h>

#include "game/entities/ui-widgets/button/UIButton.h"
#include "game/state/IGameState.h"

namespace game {

    class OverlayMenuState : public IGameState {
    public:
        OverlayMenuState(Game &game);

        ~OverlayMenuState() override = default;

        void enter() override;

        void graphicsUpdate(double t, float dt) override;

        void handleInput(const game::InputEvent &input) override;

    private:
        std::shared_ptr<UIButton> _resume_button;
        std::shared_ptr<UIButton> _restart_button;
        std::shared_ptr<UIButton> _main_menu_button;
    };

} // game

#endif //GAME_ENGINE_OVERLAYMENUSTATE_H
