#ifndef GAME_ENGINE_SPRITECOMPONENT_H
#define GAME_ENGINE_SPRITECOMPONENT_H


#include <utility>
#include <vector>
#include <memory>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "engine/math/math_utils.h"
#include "engine/entity/components/view/sprite/IAnimatedSpriteComponent.h"

namespace renderer {

    class SpriteComponent : public engine::IAnimatedSpriteComponent {
    public:
        SpriteComponent(const engine::Vector2f &size, std::weak_ptr<engine::Camera> camera, bool project_ui_space,
                        std::vector<std::shared_ptr<sf::Texture>> texture_group);

        void update(double t, float dt) override;

        std::shared_ptr<sf::Sprite> getSprite();

    private:
        std::shared_ptr<sf::Sprite> _sprite;

        std::vector<std::shared_ptr<sf::Texture>> _texture_group;

        void updateSprite() override;

        void updateSpriteRender();
    };

} // renderer

#endif //GAME_ENGINE_SPRITECOMPONENT_H
