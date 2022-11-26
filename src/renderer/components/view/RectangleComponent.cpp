#include "RectangleComponent.h"

namespace renderer {
    RectangleComponent::RectangleComponent(const engine::Vector2f &size, std::weak_ptr<engine::Camera> camera)
            : IShapeComponent(size, std::move(camera)),
              _rectangle_render(std::make_shared<sf::RectangleShape>(sf::Vector2f(0, 0))) {
        updateRectangleRender();
    }

    void RectangleComponent::update(double t, float dt, engine::Entity &entity) {
        if (_camera.expired()) {
            throw std::runtime_error("A view component has no camera");
        }
        std::shared_ptr<engine::Camera> camera_shared = _camera.lock();

        engine::Vector2f screen_position = camera_shared->projectCoordWorldToSubScreen(entity.getPosition());
        _rectangle_render->setPosition(screen_position.x, screen_position.y);

        engine::Vector2f screen_size = camera_shared->projectSizeWorldToSubScreen(_size);
        _rectangle_render->setSize({screen_size.x, screen_size.y});

        engine::Vector2f camera_scale = entity.getScale();
        _rectangle_render->setScale(camera_scale.x, camera_scale.y);

        _rectangle_render->setRotation(engine::toDegree(entity.getRotation()));
    }

    const std::shared_ptr<sf::RectangleShape> &RectangleComponent::getRectangleRender() const {
        return _rectangle_render;
    }

    void RectangleComponent::setSize(const engine::Vector2f &size) {
        IViewComponent::setSize(size);
        updateRectangleRender();
    }

    void RectangleComponent::updateShape() {
        updateRectangleRender();
    }

    void RectangleComponent::updateRectangleRender() {
        if (_camera.expired()) {
            throw std::runtime_error("A view component has no camera");
        }
        std::shared_ptr<engine::Camera> camera_shared = _camera.lock();

        _rectangle_render->setFillColor({_fillcolor.r, _fillcolor.g, _fillcolor.b, _fillcolor.a});
        _rectangle_render->setOutlineColor({_outline_color.r, _outline_color.g, _outline_color.b, _outline_color.a});
        _rectangle_render->setOutlineThickness(camera_shared->projectVerticalSizeWorldToSubScreen(_outline_thickness));

        engine::Vector2f screen_size = camera_shared->projectSizeWorldToSubScreen(_size);
        _rectangle_render->setSize({screen_size.x, screen_size.y});

        sf::FloatRect sf_rect = _rectangle_render->getLocalBounds();
        _rectangle_render->setOrigin(sf_rect.left + sf_rect.width / 2, sf_rect.top + sf_rect.height / 2);
    }
} // renderer