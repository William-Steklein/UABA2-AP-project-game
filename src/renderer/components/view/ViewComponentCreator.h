#ifndef GAME_ENGINE_VIEWCOMPONENTCREATOR_H
#define GAME_ENGINE_VIEWCOMPONENTCREATOR_H


#include <utility>
#include <vector>
#include <map>

#include "engine/entity/components/view/IViewComponentCreator.h"

#include "renderer/components/view/ViewComponent.h"
#include "renderer/resources/ResourceManager.h"

namespace renderer {

    class ViewComponentCreator : public engine::IViewComponentCreator {
    public:
        ViewComponentCreator(std::shared_ptr<ResourceManager> resource_manager);

        ~ViewComponentCreator() = default;

        std::shared_ptr<engine::IViewComponent> create(const std::string &texture_id, unsigned int layer) override;

        std::vector<std::shared_ptr<ViewComponent>> getEntityViews();

    private:
        std::shared_ptr<ResourceManager> _resource_manager;

        std::map<unsigned int, std::vector<std::weak_ptr<ViewComponent>>> _view_components;
    };

} // renderer

#endif //GAME_ENGINE_VIEWCOMPONENTCREATOR_H
