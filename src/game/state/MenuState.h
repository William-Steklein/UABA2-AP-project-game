#ifndef GAME_ENGINE_MENUSTATE_H
#define GAME_ENGINE_MENUSTATE_H


#include <engine/entity/ui/UIEntity.h>

#include "game/entities/widgets/UIButton.h"
#include "game/state/IGameState.h"

namespace game {

    class MenuState : public IGameState {
    public:
        MenuState();

        ~MenuState() override = default;

        void enter(game::Game &game) override;

        void update(game::Game &game, double t, float dt) override;

        void handleInput(game::Game &game, const game::InputEvent &input) override;

        void checkButtons();

        void toggleKeyboardFocus(bool keyboard_focus);

        void selectNextButton(bool up);

    private:
        std::vector<std::shared_ptr<UIButton>> _buttons;
        bool _keyboard_focus;
        int _selected_button_index;

        std::shared_ptr<UIButton> _play_button;
        std::shared_ptr<UIButton> _debug_button;
        std::shared_ptr<UIButton> _quit_button;
    };

} // game

#endif //GAME_ENGINE_MENUSTATE_H
