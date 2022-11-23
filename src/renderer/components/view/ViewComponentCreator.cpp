#include "ViewComponentCreator.h"

namespace renderer {
    ViewComponentCreator::ViewComponentCreator(std::shared_ptr<ResourceManager> resource_manager)
            : _resource_manager(std::move(resource_manager)) {

    }

    ViewComponentCreator::~ViewComponentCreator() = default;

    std::shared_ptr<engine::IViewComponent>
    ViewComponentCreator::create(const std::string &texture_id, unsigned int layer) {
        std::shared_ptr<ViewComponent> entity_view = std::make_shared<ViewComponent>(
                _camera, _resource_manager->getTextureGroup(texture_id));

        std::weak_ptr<ViewComponent> entity_view_weak = entity_view;
        if (_view_components.count(layer)) {
            _view_components.at(layer).push_back(entity_view_weak);
        } else {
            _view_components[layer] = {entity_view_weak};
        }

        return entity_view;
    }

    std::vector<std::shared_ptr<ViewComponent>> ViewComponentCreator::getEntityViews() {
        std::vector<std::shared_ptr<ViewComponent>> render_views;

        for (auto &layer: _view_components) {
            for (auto it = layer.second.begin(); it != layer.second.end();) {
                // if the entityview got destroyed, remove it from the set
                if ((*it).expired()) {
                    it = layer.second.erase(it);
                } else {
                    render_views.push_back((*it).lock());

                    it++;
                }
            }
        }

        return render_views;
    }
} // renderer