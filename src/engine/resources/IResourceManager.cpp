#include "IResourceManager.h"

namespace engine {

    void
    IResourceManager::loadAnimationResourceGroups(
            const std::vector<AnimationResourceGroup> &animation_resource_groups) {
        for (const auto &animation_resource_group: animation_resource_groups) {
            std::shared_ptr<AnimationGroup> animation_group = std::make_shared<AnimationGroup>();
            animation_group->id = animation_resource_group.id;

            unsigned int current_texture_count = 0;

            for (const auto &animation_resource: animation_resource_group.animation_resources) {
                Animation animation{};
                animation.frame_time = animation_resource.second.frame_time;

                if (animation.frame_time <= constants::animation_frame_time_minimum) {
                    throw std::runtime_error("Animation \"" + animation_resource.first + "\" in \"" +
                                             animation_group->id + "\" has a frame time lower than \"" +
                                             std::to_string(constants::animation_frame_time_minimum) + "\"");
                }

                animation.start_frame = current_texture_count;
                current_texture_count += animation_resource.second.frame_paths.size();
                animation.end_frame = current_texture_count - 1;

                animation_group->animations[animation_resource.first] = animation;
            }

            _animation_groups[animation_resource_group.id] = animation_group;
        }
    }

    std::shared_ptr<AnimationGroup> IResourceManager::getAnimationGroup(const std::string &animation_id) {
        return _animation_groups[animation_id];
    }

} // engine