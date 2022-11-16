#ifndef GAME_ENGINE_ANIMATIONRESOURCE_H
#define GAME_ENGINE_ANIMATIONRESOURCE_H


#include <string>
#include <vector>

namespace engine {

    struct AnimationResource {
        std::vector<std::string> frame_paths;
        float frame_time;
    };

    struct AnimationResourceGroup {
        std::string name;
        std::vector<AnimationResource> animation_resources;
    };

} // engine


#endif //GAME_ENGINE_ANIMATIONRESOURCE_H
