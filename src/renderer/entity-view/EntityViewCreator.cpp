#include "EntityViewCreator.h"

namespace renderer {
    EntityViewCreator::EntityViewCreator(std::shared_ptr<ResourceManager> resource_manager)
            : _resource_manager(std::move(resource_manager)) {

    }

    EntityViewCreator::~EntityViewCreator() = default;

    std::shared_ptr<engine::IViewComponent>
    EntityViewCreator::create(const std::string &texture_id, unsigned int layer) {
        std::shared_ptr<EntityView> entity_view = std::make_shared<EntityView>(
                _resource_manager->getTextureGroup(texture_id));

        std::weak_ptr<EntityView> entity_view_weak = entity_view;
        if (_entity_views.count(layer)) {
            _entity_views.at(layer).push_back(entity_view_weak);
        } else {
            _entity_views[layer] = {entity_view_weak};
        }

        return entity_view;
    }

    std::vector<std::shared_ptr<EntityView>> EntityViewCreator::getEntityViews() {
        std::vector<std::shared_ptr<EntityView>> render_views;

        for (auto &layer: _entity_views) {
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