#ifndef GAME_ENGINE_ENTITYVIEWCREATOR_H
#define GAME_ENGINE_ENTITYVIEWCREATOR_H


#include <utility>
#include <vector>
#include <map>

#include <engine/entities/IEntityViewCreator.h>
#include "renderer/entity-view/EntityView.h"
#include "renderer/resources/ResourceManager.h"

namespace renderer {

    class EntityViewCreator : public engine::IEntityViewCreator {
    public:
        EntityViewCreator(std::shared_ptr<ResourceManager> resource_manager);

        ~EntityViewCreator();

        std::shared_ptr<engine::IEntityView> create(const std::string &texture_id, unsigned int layer) override;

        std::vector<std::shared_ptr<EntityView>> getEntityViews();

    private:
        std::shared_ptr<ResourceManager> _resource_manager;

        std::map<unsigned int, std::vector<std::weak_ptr<EntityView>>> _entity_views;
    };

} // renderer

#endif //GAME_ENGINE_ENTITYVIEWCREATOR_H
