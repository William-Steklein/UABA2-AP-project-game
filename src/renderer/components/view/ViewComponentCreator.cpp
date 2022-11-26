#include "ViewComponentCreator.h"

namespace renderer {
    ViewComponentCreator::ViewComponentCreator(std::shared_ptr<ResourceManager> resource_manager)
            : _resource_manager(std::move(resource_manager)) {

    }

    std::shared_ptr<engine::ILineComponent> ViewComponentCreator::createLine(
            const engine::Vector2f &size, unsigned int layer) {
        return std::shared_ptr<engine::ILineComponent>();
    }

    std::shared_ptr<engine::IShapeComponent> ViewComponentCreator::createRectangle(
            const engine::Vector2f &size, unsigned int layer) {
        std::shared_ptr<RectangleComponent> rectangle_component = std::make_shared<RectangleComponent>(size, _camera);

        insertDrawable(rectangle_component->getRectangleRender(), layer);

        return rectangle_component;
    }

    std::shared_ptr<engine::ISpriteComponent> ViewComponentCreator::createSprite(
            const engine::Vector2f &size, unsigned int layer, const std::string &texture_id) {
        std::shared_ptr<SpriteComponent> sprite_component =
                std::make_shared<SpriteComponent>(size, _camera, _resource_manager->getTextureGroup(texture_id));

        insertDrawable(sprite_component->getSprite(), layer);

        return sprite_component;
    }

    std::shared_ptr<engine::IAnimatedSpriteComponent> ViewComponentCreator::createAnimatedSprite(
            const engine::Vector2f &size, unsigned int layer, const std::string &animation_group_id) {
        std::shared_ptr<SpriteComponent> animated_sprite_component =
                std::make_shared<SpriteComponent>(size, _camera,
                                                  _resource_manager->getTextureGroup(animation_group_id));
        animated_sprite_component->setAnimationGroup(
                std::move(_resource_manager->getAnimationGroup(animation_group_id)));

        insertDrawable(animated_sprite_component->getSprite(), layer);

        return animated_sprite_component;
    }

    std::shared_ptr<engine::ITextBoxComponent> ViewComponentCreator::createTextBox(
            const engine::Vector2f &size, unsigned int layer, const std::string &font) {
        std::shared_ptr<TextBoxComponent> text_component =
                std::make_shared<TextBoxComponent>(size, _camera, _resource_manager->getFont(font));

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