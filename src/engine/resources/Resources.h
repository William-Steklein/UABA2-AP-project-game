#ifndef GAME_ENGINE_RESOURCES_H
#define GAME_ENGINE_RESOURCES_H


#include <string>
#include <vector>
#include <map>

namespace engine {

    struct TextureResource {
        std::string id;
        std::string texture_path;
    };

    struct AnimationResource {
        float frame_time;
        std::vector<std::string> frame_paths;
    };

    struct AnimationResourceGroup {
        std::string id;
        std::map<std::string, AnimationResource> animation_resources;
    };

    struct AudioResource {
        std::string id;
        std::string audio_path;
    };

} // engine

#endif //GAME_ENGINE_RESOURCES_H
