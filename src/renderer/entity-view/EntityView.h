#ifndef GAME_ENGINE_ENTITYVIEW_H
#define GAME_ENGINE_ENTITYVIEW_H


#include <utility>
#include <vector>
#include <memory>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <engine/entities/Entity.h>
#include <engine/entities/components/IEntityView.h>
#include <engine/math/math_utils.h>

namespace renderer {

    class EntityView : public engine::IEntityView {
    public:
        EntityView(std::vector<std::shared_ptr<sf::Texture>> texture_group);

        void update(double t, float dt, engine::Entity &entity) override;

        void setTexture(unsigned int texture_index, bool mirror_h, bool mirror_v) override;

        std::shared_ptr<sf::Sprite> getSprite();

    private:
        std::shared_ptr<sf::Sprite> _sprite;

        std::vector<std::shared_ptr<sf::Texture>> _texture_group;

        void updateSpriteTexture();
    };

} // renderer

#endif //GAME_ENGINE_ENTITYVIEW_H
