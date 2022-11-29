#ifndef GAME_ENGINE_UIBUTTON_H
#define GAME_ENGINE_UIBUTTON_H


#include <engine/entity/ui/UIEntity.h>
#include <engine/physics/HitBox.h>

#include "game/input/InputEvent.h"

namespace game {

    class UIButton : public engine::UIEntity {
    public:
        enum State {
            BUTTON_INACTIVE,
            BUTTON_HOVER,
            BUTTON_CLICKED,
            BUTTON_ACTIVE
        };

        UIButton(engine::Transform transform, std::shared_ptr<engine::Vector2f> mouse_position,
                 const std::vector<std::shared_ptr<engine::IComponent>> &components = {});

        ~UIButton() override = default;

        void handleInput(const InputEvent &input);

        const std::shared_ptr<engine::HitBox> &getHitBox() const;

        bool isActive() const;

        bool mouseCollides() const;

    private:
        std::shared_ptr<engine::Vector2f> _mouse_position;
        std::shared_ptr<engine::HitBox> _hit_box;

        State _state;
    };

} // game

#endif //GAME_ENGINE_UIBUTTON_H
