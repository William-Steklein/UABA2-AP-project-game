#ifndef GAME_ENGINE_VIEWCOMPONENT_H
#define GAME_ENGINE_VIEWCOMPONENT_H


#include <utility>
#include <vector>
#include <memory>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "engine/math/math_utils.h"
#include "engine/entity/Entity.h"
#include "engine/entity/components/view/IViewComponent.h"

namespace renderer {

    class ViewComponent : public engine::IViewComponent {
    public:
        ViewComponent(std::weak_ptr<engine::Camera> camera,
                      std::vector<std::shared_ptr<sf::Texture>> texture_group);

        void update(double t, float dt, engine::Entity &entity) override;

        void setTexture(unsigned int texture_index, bool mirror_h, bool mirror_v) override;

        std::shared_ptr<sf::Sprite> getSprite();

    private:
        std::shared_ptr<sf::Sprite> _sprite;

        std::vector<std::shared_ptr<sf::Texture>> _texture_group;

        void updateSpriteTexture();
    };

} // renderer

#endif //GAME_ENGINE_VIEWCOMPONENT_H
