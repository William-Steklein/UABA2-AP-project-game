#ifndef GAME_ENGINE_BUTTON_H
#define GAME_ENGINE_BUTTON_H

#include <engine/entity/ui/UIEntity.h>
#include <engine/entity/components/physics/HitBox.h>
#include <engine/entity/components/view/sprite/IAnimatedSpriteComponent.h>


#include "game/input/InputEvent.h"

namespace game {

    class ButtonState;

    class Button : public engine::UIEntity {
    public:
        std::shared_ptr<engine::IAnimatedSpriteComponent> _animated_sprite;

        Button(engine::Transform transform, const engine::Vector2f &hit_box_size,
               std::shared_ptr<engine::Vector2f> mouse_position,
               std::shared_ptr<engine::IAnimatedSpriteComponent> animated_sprite,
               const std::vector<std::shared_ptr<engine::IComponent>> &components = {});

        void handleInput(const InputEvent &input);

        bool isActive() const;

        bool mouseCollides() const;

        void reset();

    private:
        std::unique_ptr<ButtonState> _state;

        std::shared_ptr<engine::Vector2f> _mouse_position;
        std::shared_ptr<engine::HitBox> _hit_box;
    };

} // game

#endif //GAME_ENGINE_BUTTON_H
