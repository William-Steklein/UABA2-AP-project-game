#ifndef GAME_ENGINE_OVERLAYMENUSTATE_H
#define GAME_ENGINE_OVERLAYMENUSTATE_H


#include <engine/entity/ui/UIEntity.h>

#include "game/entities/widgets/UIButton.h"
#include "game/state/IGameState.h"
#include "game/Game.h"

namespace game {

    class OverlayMenuState : public IGameState {
    public:
        OverlayMenuState() = default;

        ~OverlayMenuState() override = default;

        void enter(game::Game &game) override;

        void update(game::Game &game, double t, float dt) override;

        void handleInput(game::Game &game, const game::InputEvent &input) override;

    private:
        std::shared_ptr<UIButton> _resume_button;
        std::shared_ptr<UIButton> _restart_button;
        std::shared_ptr<UIButton> _main_menu_button;
    };

} // game

#endif //GAME_ENGINE_OVERLAYMENUSTATE_H
