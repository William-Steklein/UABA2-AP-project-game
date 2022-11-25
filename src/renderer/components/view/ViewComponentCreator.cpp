#include "ViewComponentCreator.h"

namespace renderer {
    ViewComponentCreator::ViewComponentCreator(std::shared_ptr<ResourceManager> resource_manager)
            : _resource_manager(std::move(resource_manager)) {

    }

    std::shared_ptr<engine::ISpriteComponent>
    ViewComponentCreator::createSprite(const engine::Vector2f &size, const std::string &texture_id,
                                       unsigned int layer) {
        std::shared_ptr<SpriteComponent> sprite_component =
                std::make_shared<SpriteComponent>(size, _camera, _resource_manager->getTextureGroup(texture_id));

        insertDrawable(sprite_component->getSprite(), layer);

        return sprite_component;
    }

    std::shared_ptr<engine::IAnimatedSpriteComponent>
    ViewComponentCreator::createAnimatedSprite(const engine::Vector2f &size, const std::string &animation_group_id,
                                               unsigned int layer) {
        std::shared_ptr<SpriteComponent> animated_sprite_component =
                std::make_shared<SpriteComponent>(size, _camera, _resource_manager->getTextureGroup(animation_group_id));
        animated_sprite_component->setAnimationGroup(
                std::move(_resource_manager->getAnimationGroup(animation_group_id)));

        insertDrawable(animated_sprite_component->getSprite(), layer);

        return animated_sprite_component;
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