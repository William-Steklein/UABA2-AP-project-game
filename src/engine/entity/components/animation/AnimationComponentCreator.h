#ifndef GAME_ENGINE_ANIMATIONCOMPONENTCREATOR_H
#define GAME_ENGINE_ANIMATIONCOMPONENTCREATOR_H


#include <utility>
#include <memory>

#include "AnimationComponent.h"
#include "engine/resources/IResourceManager.h"
#include "engine/entity/components/view/IViewComponentCreator.h"

namespace engine {

    class AnimationComponentCreator {
    public:
        AnimationComponentCreator(std::shared_ptr<IResourceManager> resource_manager,
                                  std::shared_ptr<IViewComponentCreator> entity_view_creator);

        ~AnimationComponentCreator() = default;

        std::shared_ptr<AnimationComponent> create(const std::string &animation_group_id, unsigned int layer) const;

    private:
        std::shared_ptr<IResourceManager> _resource_manager;
        std::shared_ptr<IViewComponentCreator> _entity_view_creator;
    };

} // engine

#endif //GAME_ENGINE_ANIMATIONCOMPONENTCREATOR_H
