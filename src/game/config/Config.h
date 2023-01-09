#ifndef GAME_ENGINE_CONFIG_H
#define GAME_ENGINE_CONFIG_H


#include <string>
#include <map>

#include "engine/input/Input.h"
#include "engine/constants/constants.h"

#include "game/input/InputEvent.h"

namespace game {

    struct Config {
        struct ButtonMap {
            std::map<engine::Input::Button, game::InputEvent::Type> keyboard;
        };

        struct Audio {
            unsigned int master;
            unsigned int sfx;
            unsigned int music;
        };

        ButtonMap button_map;
        Audio audio;

        bool show_framerate = engine::constants::show_framerate;
        bool framerate_cap = engine::constants::framerate_cap;
        float framerate_limit = engine::constants::framerate_limit;
    };

} // game

#endif //GAME_ENGINE_CONFIG_H
