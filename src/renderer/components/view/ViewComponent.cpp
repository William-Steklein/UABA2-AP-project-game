#include "ViewComponent.h"

namespace renderer {
    ViewComponent::ViewComponent(std::weak_ptr<engine::Camera> camera,
                                 std::vector<std::shared_ptr<sf::Texture>> texture_group)
            : engine::IViewComponent(std::move(camera)), _texture_group(std::move(texture_group)),
              _sprite(std::make_shared<sf::Sprite>()) {
        updateSpriteTexture();
    }

    void ViewComponent::update(double t, float dt, engine::Entity &entity) {
        if (_camera.expired()) {
            throw std::runtime_error("A view component has no camera");
        }

        std::shared_ptr<engine::Camera> camera_shared = _camera.lock();

        // update sprite transform
        engine::Vector2f screen_position = camera_shared->projectCoordWorldToSubScreen(entity.getPosition());
        _sprite->setPosition(screen_position.x, screen_position.y);

        auto texture_size = _sprite->getTexture()->getSize();

        engine::Vector2f camera_size = entity.getScale();
        engine::Vector2f screen_size = camera_shared->projectSizeWorldToSubScreen(entity.getScale());

        float x_scale_factor = screen_size.x / (camera_size.x * static_cast<float>(texture_size.x));

        float y_scale_factor = screen_size.y / (camera_size.y * static_cast<float>(texture_size.y));

        _sprite->setScale(_mirror_h ? -x_scale_factor : x_scale_factor,
                          _mirror_v ? -y_scale_factor : y_scale_factor);

        _sprite->setRotation(engine::toDegree(entity.getRotation()));
    }

    void ViewComponent::setTexture(unsigned int texture_index, bool mirror_h, bool mirror_v) {
        IViewComponent::setTexture(texture_index, mirror_h, mirror_v);

        updateSpriteTexture();
    }

    std::shared_ptr<sf::Sprite> ViewComponent::getSprite() {
        return _sprite;
    }

    void ViewComponent::updateSpriteTexture() {
        _sprite->setTexture(*_texture_group.at(_texture_index), true);
        _sprite->setOrigin(static_cast<float>(_sprite->getTextureRect().width) / 2,
                           static_cast<float>(_sprite->getTextureRect().height) / 2);
    }
} // renderer