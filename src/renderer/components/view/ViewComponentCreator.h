#ifndef GAME_ENGINE_VIEWCOMPONENTCREATOR_H
#define GAME_ENGINE_VIEWCOMPONENTCREATOR_H


#include <utility>
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>

#include "engine/entity/components/view/IViewComponentCreator.h"

#include "renderer/resources/ResourceManager.h"
#include "renderer/components/view/SpriteComponent.h"
#include "renderer/components/view/TextBoxComponent.h"

namespace renderer {

    class ViewComponentCreator : public engine::IViewComponentCreator {
    public:
        ViewComponentCreator(std::shared_ptr<ResourceManager> resource_manager);

        ~ViewComponentCreator() = default;

        std::shared_ptr<engine::ISpriteComponent> createSprite(
                const engine::Vector2f &size, unsigned int layer, const std::string &texture_id) override;

        std::shared_ptr<engine::IAnimatedSpriteComponent> createAnimatedSprite(
                const engine::Vector2f &size, unsigned int layer, const std::string &animation_group_id) override;

        std::shared_ptr<engine::ITextBoxComponent> createTextBox(
                const engine::Vector2f &size, unsigned int layer, const std::string &font,
                float font_size, const engine::Color &color, const std::string &text) override;

        void draw(const std::shared_ptr<sf::RenderWindow> &window);

    private:
        std::shared_ptr<ResourceManager> _resource_manager;

        std::map<unsigned int, std::vector<std::weak_ptr<sf::Drawable>>> _drawables;

        void insertDrawable(const std::weak_ptr<sf::Drawable> &view_component, unsigned int layer);
    };

} // renderer

#endif //GAME_ENGINE_VIEWCOMPONENTCREATOR_H
