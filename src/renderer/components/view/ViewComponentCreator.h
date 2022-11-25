#ifndef GAME_ENGINE_VIEWCOMPONENTCREATOR_H
#define GAME_ENGINE_VIEWCOMPONENTCREATOR_H


#include <utility>
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>

#include "engine/entity/components/view/IViewComponentCreator.h"

#include "renderer/components/view/SpriteComponent.h"
#include "renderer/resources/ResourceManager.h"

namespace renderer {

    class ViewComponentCreator : public engine::IViewComponentCreator {
    public:
        ViewComponentCreator(std::shared_ptr<ResourceManager> resource_manager);

        ~ViewComponentCreator() = default;

        std::shared_ptr<engine::ISpriteComponent> createSprite(const engine::Vector2f &size,
                                                               const std::string &texture_id,
                                                               unsigned int layer) override;

        std::shared_ptr<engine::IAnimatedSpriteComponent> createAnimatedSprite(const engine::Vector2f &size,
                                                                               const std::string &animation_group_id,
                                                                               unsigned int layer) override;

        void draw(const std::shared_ptr<sf::RenderWindow> &window);

    private:
        std::shared_ptr<ResourceManager> _resource_manager;

        std::map<unsigned int, std::vector<std::weak_ptr<sf::Drawable>>> _drawables;

        void insertDrawable(const std::weak_ptr<sf::Drawable> &view_component, unsigned int layer);
    };

} // renderer

#endif //GAME_ENGINE_VIEWCOMPONENTCREATOR_H
