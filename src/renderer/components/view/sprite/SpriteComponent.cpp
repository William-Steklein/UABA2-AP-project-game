#include "SpriteComponent.h"

namespace renderer {
    SpriteComponent::SpriteComponent(const engine::Vector2f &size, std::weak_ptr<engine::Camera> camera,
                                     bool project_ui_space,
                                     std::vector<std::shared_ptr<sf::Texture>> texture_group)
            : engine::IAnimatedSpriteComponent(size, std::move(camera), project_ui_space),
            _texture_group(std::move(texture_group)),
              _sprite(std::make_shared<sf::Sprite>()) {
        updateSpriteRender();
    }

    void SpriteComponent::update(double t, float dt, engine::Transform &transform) {
        engine::IAnimatedSpriteComponent::update(t, dt, transform);

        if (_camera.expired()) {
            throw std::runtime_error("A view component has no camera");
        }

        std::shared_ptr<engine::Camera> camera_shared = _camera.lock();

        // update sprite transform
        engine::Vector2f screen_position = camera_shared->projectCoordWorldToSubScreen(transform.position,
                                                                                       _project_ui_space);
        _sprite->setPosition(screen_position.x, screen_position.y);

        auto texture_size = _sprite->getTexture()->getSize();

        engine::Vector2f camera_scale = transform.scale;
        engine::Vector2f screen_size = camera_shared->projectSizeWorldToSubScreen(_size);

        float x_scale_factor = (screen_size.x / static_cast<float>(texture_size.x)) * camera_scale.x;

        float y_scale_factor = (screen_size.y / static_cast<float>(texture_size.y)) * camera_scale.y;

        _sprite->setScale(_mirror_h ? -x_scale_factor : x_scale_factor,
                          _mirror_v ? -y_scale_factor : y_scale_factor);

        _sprite->setRotation(engine::toDegree(transform.rotation));
    }

    std::shared_ptr<sf::Sprite> SpriteComponent::getSprite() {
        return _sprite;
    }

    void SpriteComponent::updateSprite() {
        updateSpriteRender();
    }

    void SpriteComponent::updateSpriteRender() {
        _sprite->setTexture(*_texture_group.at(_texture_index), true);
        _sprite->setOrigin(static_cast<float>(_sprite->getTextureRect().width) / 2,
                           static_cast<float>(_sprite->getTextureRect().height) / 2);
    }
} // renderer