#ifndef GAME_ENGINE_RECTANGLEVIEWCOMPONENT_H
#define GAME_ENGINE_RECTANGLEVIEWCOMPONENT_H


#include <SFML/Graphics/RectangleShape.hpp>

#include "engine/entity/components/view/shape/ILineComponent.h"

namespace renderer {

    class RectangleComponent : public engine::ILineComponent {
    public:
        RectangleComponent(std::weak_ptr<engine::Camera> camera, bool project_ui_space);

        ~RectangleComponent() = default;

        void update(double t, float dt) override;

        const std::shared_ptr<sf::RectangleShape> &getRectangleRender() const;

        void setSize(const engine::Vector2f &size) override;

    private:
        std::shared_ptr<sf::RectangleShape> _rectangle_render;

        void updateShape() override;

        void updateRectangleRender();
    };

} // renderer

#endif //GAME_ENGINE_RECTANGLEVIEWCOMPONENT_H
