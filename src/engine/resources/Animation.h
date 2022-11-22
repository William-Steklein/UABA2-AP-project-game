#ifndef GAME_ENGINE_ANIMATION_H
#define GAME_ENGINE_ANIMATION_H


#include <string>
#include <vector>
#include <map>

namespace engine {

    struct Animation {
        float frame_time;
        unsigned int start_frame;
        unsigned int end_frame;
    };

    struct AnimationGroup {
        std::string id;
        std::map<std::string, Animation> animations;
    };

} // engine

#endif //GAME_ENGINE_ANIMATION_H
