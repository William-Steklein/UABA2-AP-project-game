#ifndef GAME_ENGINE_CONFIG_H
#define GAME_ENGINE_CONFIG_H


#include <string>
#include <map>

#include <engine/Input.h>

#include "game/InputEvent.h"

namespace game {

    struct Config {
        struct ButtonMap {
            std::map<engine::Input::Button, game::InputEvent::Type> keyboard;
//            std::map<engine::Input::Button, game::InputEvent::Type> controller;
        };

        struct Video {
            unsigned int width;
            unsigned int height;
            bool full_screen;
        };

        struct Audio {
            unsigned int master;
            unsigned int sfx;
            unsigned int music;
        };

        ButtonMap button_map;
        Video video;
        Audio audio;
    };

} // game

#endif //GAME_ENGINE_CONFIG_H
