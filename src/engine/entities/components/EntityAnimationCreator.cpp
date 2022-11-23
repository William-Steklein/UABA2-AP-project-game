#include "EntityAnimationCreator.h"

namespace engine {
    EntityAnimationCreator::EntityAnimationCreator(std::shared_ptr<IResourceManager> resource_manager,
                                                   std::shared_ptr<IEntityViewCreator> entity_view_creator)
            : _resource_manager(std::move(resource_manager)), _entity_view_creator(std::move(entity_view_creator)) {

    }

    std::shared_ptr<EntityAnimation>
    EntityAnimationCreator::create(const std::string &animation_group_id, unsigned int layer) const {
        std::shared_ptr<EntityAnimation> entity_animation = std::make_shared<EntityAnimation>(
                _resource_manager->getAnimationGroup(animation_group_id));

        entity_animation->setView(_entity_view_creator->create(animation_group_id, layer));

        return entity_animation;
    }
} // engine