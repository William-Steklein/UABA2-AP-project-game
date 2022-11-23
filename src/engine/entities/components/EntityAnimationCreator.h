#ifndef GAME_ENGINE_ENTITYANIMATIONCREATOR_H
#define GAME_ENGINE_ENTITYANIMATIONCREATOR_H


#include <utility>
#include <memory>

#include "engine/entities/components/EntityAnimation.h"
#include "engine/resources/IResourceManager.h"
#include "engine/entities/IEntityViewCreator.h"

namespace engine {

    class EntityAnimationCreator {
    public:
        EntityAnimationCreator(std::shared_ptr<IResourceManager> resource_manager,
                               std::shared_ptr<IEntityViewCreator> entity_view_creator);

        ~EntityAnimationCreator() = default;

        std::shared_ptr<EntityAnimation> create(const std::string &animation_group_id, unsigned int layer) const;

    private:
        std::shared_ptr<IResourceManager> _resource_manager;
        std::shared_ptr<IEntityViewCreator> _entity_view_creator;
    };

} // engine

#endif //GAME_ENGINE_ENTITYANIMATIONCREATOR_H
