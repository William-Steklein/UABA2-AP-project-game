#include "EntityView.h"

namespace renderer {
    EntityView::EntityView(std::vector<std::shared_ptr<sf::Texture>> texture_group)
            : engine::IEntityView(), _texture_group(std::move(texture_group)), _sprite(std::make_shared<sf::Sprite>()) {
        updateSpriteTexture();
    }

    void EntityView::update(double t, float dt, engine::Entity &entity) {
        // transform
        engine::Vector2f pos = entity.getPosition();
//            engine::Vector2f new_position = entity_shared->getScreenPosition();
//            _sprite.setPosition(new_position.x, new_position.y);

        auto texture_size = _sprite->getTexture()->getSize();
        engine::Vector2f entity_size = entity.getScale();

//            float x_scale_factor = entity_shared->getScreenViewSize().x /
//                                   static_cast<float>(texture_size.x) *
//                                   entity_size.x;
//
//            float y_scale_factor = entity_shared->getScreenViewSize().y /
//                                   static_cast<float>(texture_size.y) *
//                                   entity_size.y;

//            _sprite.setScale(_mirror_h ? -x_scale_factor : x_scale_factor,
//                             _mirror_v ? -y_scale_factor : y_scale_factor);

        _sprite->setRotation(engine::toDegree(entity.getRotation()));
    }

    void EntityView::setTexture(unsigned int texture_index, bool mirror_h, bool mirror_v) {
        IEntityView::setTexture(texture_index, mirror_h, mirror_v);

        updateSpriteTexture();
    }

    std::shared_ptr<sf::Sprite> EntityView::getSprite() {
        return _sprite;
    }

    void EntityView::updateSpriteTexture() {
        _sprite->setTexture(*_texture_group.at(_texture_index), true);
        _sprite->setOrigin(static_cast<float>(_sprite->getTextureRect().width) / 2,
                           static_cast<float>(_sprite->getTextureRect().height) / 2);
    }
} // renderer