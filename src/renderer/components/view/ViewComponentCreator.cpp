#include "ViewComponentCreator.h"

namespace renderer {
    ViewComponentCreator::ViewComponentCreator(std::shared_ptr<ResourceManager> resource_manager)
            : _resource_manager(std::move(resource_manager)) {

    }

    std::shared_ptr<engine::ILineComponent> ViewComponentCreator::createLine(
            unsigned int layer, bool project_ui_space, const engine::Vector2f &origin,
            const engine::Vector2f &end) {
        std::shared_ptr<RectangleComponent> line_component =
                std::make_shared<RectangleComponent>(_camera, project_ui_space);

        line_component->setLine(origin, end);

        insertDrawable(line_component->getRectangleRender(), layer);

        return line_component;
    }

    std::shared_ptr<engine::IShapeComponent> ViewComponentCreator::createRectangle(
            const engine::Vector2f &size, unsigned int layer, bool project_ui_space) {
        std::shared_ptr<RectangleComponent> rectangle_component =
                std::make_shared<RectangleComponent>(_camera, project_ui_space);

        rectangle_component->setSize(size);

        insertDrawable(rectangle_component->getRectangleRender(), layer);

        return rectangle_component;
    }

    std::shared_ptr<engine::ISpriteComponent> ViewComponentCreator::createSprite(
            const engine::Vector2f &size, unsigned int layer, bool project_ui_space,
            const std::string &texture_id) {
        std::shared_ptr<SpriteComponent> sprite_component =
                std::make_shared<SpriteComponent>(size, _camera, project_ui_space,
                                                  _resource_manager->getTextureGroup(texture_id));

        insertDrawable(sprite_component->getSprite(), layer);

        return sprite_component;
    }

    std::shared_ptr<engine::IAnimatedSpriteComponent> ViewComponentCreator::createAnimatedSprite(
            const engine::Vector2f &size, unsigned int layer, bool project_ui_space,
            const std::string &animation_group_id) {
        std::shared_ptr<SpriteComponent> animated_sprite_component =
                std::make_shared<SpriteComponent>(size, _camera, project_ui_space,
                                                  _resource_manager->getTextureGroup(animation_group_id));
        animated_sprite_component->setAnimationGroup(
                std::move(_resource_manager->getAnimationGroup(animation_group_id)));

        insertDrawable(animated_sprite_component->getSprite(), layer);

        return animated_sprite_component;
    }

    std::shared_ptr<engine::ITextBoxComponent> ViewComponentCreator::createTextBox(
            const engine::Vector2f &size, unsigned int layer, bool project_ui_space, const std::string &font) {
        std::shared_ptr<TextBoxComponent> text_component =
                std::make_shared<TextBoxComponent>(size, _camera, project_ui_space, _resource_manager->getFont(font));

        insertDrawable(text_component->getTextRender(), layer);

        return text_component;
    }

    void ViewComponentCreator::draw(const std::shared_ptr<sf::RenderWindow> &window) {
        for (auto &layer: _drawables) {
            for (auto view_component_it = layer.second.begin(); view_component_it != layer.second.end();) {
                // if the view component got destroyed, remove it from the set
                if ((*view_component_it).expired()) {
                    view_component_it = layer.second.erase(view_component_it);
                } else {
                    window->draw(*(*view_component_it).lock());

                    view_component_it++;
                }
            }
        }
    }

    void ViewComponentCreator::insertDrawable(const std::weak_ptr<sf::Drawable> &view_component, unsigned int layer) {
        if (_drawables.count(layer)) {
            _drawables.at(layer).push_back(view_component);
        } else {
            _drawables[layer] = {view_component};
        }
    }
} // renderer