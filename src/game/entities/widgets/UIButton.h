#ifndef GAME_ENGINE_UIBUTTON_H
#define GAME_ENGINE_UIBUTTON_H


#include <engine/entity/ui/UIEntity.h>
#include <engine/physics/HitBox.h>
#include <engine/entity/components/view/sprite/IAnimatedSpriteComponent.h>

#include "game/input/InputEvent.h"

namespace game {

    class UIButton : public engine::UIEntity {
    public:
        enum State {
            BUTTON_INACTIVE,
            BUTTON_HOVER,
            BUTTON_CLICKING,
            BUTTON_CLICKED,
            BUTTON_ACTIVE
        };

        UIButton(engine::Transform transform, const engine::Vector2f &hit_box_size,
                 std::shared_ptr<engine::Vector2f> mouse_position,
                 std::shared_ptr<engine::IAnimatedSpriteComponent> animated_sprite,
                 const std::vector<std::shared_ptr<engine::IComponent>> &components = {});

        ~UIButton() override = default;

        void handleInput(const InputEvent &input);

        const std::shared_ptr<engine::HitBox> &getHitBox() const;

        bool isActive() const;

        bool mouseCollides() const;

        void reset();

    private:
        std::shared_ptr<engine::Vector2f> _mouse_position;
        std::shared_ptr<engine::HitBox> _hit_box;

        State _state;

        std::shared_ptr<engine::IAnimatedSpriteComponent> _animated_sprite;
    };

} // game

#endif //GAME_ENGINE_UIBUTTON_H
