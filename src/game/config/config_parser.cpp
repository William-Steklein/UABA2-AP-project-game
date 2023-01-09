#include "config_parser.h"
#include "engine/utils/file_io.h"

namespace game {
    Config parseConfig(const std::string &filepath) {
        Config config;
        nlohmann::json j = engine::loadJsonFromFile(filepath);

        nlohmann::json k_map = j["button_map"]["keyboard"];
        config.button_map.keyboard[engine::stringToInputButton(k_map["left"])] = game::InputEvent::Type::LEFT;
        config.button_map.keyboard[engine::stringToInputButton(k_map["right"])] = game::InputEvent::Type::RIGHT;
        config.button_map.keyboard[engine::stringToInputButton(k_map["down"])] = game::InputEvent::Type::DOWN;
        config.button_map.keyboard[engine::stringToInputButton(k_map["jump"])] = game::InputEvent::Type::JUMP;
        config.button_map.keyboard[engine::stringToInputButton(
                k_map["debug_view"])] = game::InputEvent::Type::DEBUGVIEW;

        config.button_map.keyboard[engine::Input::Button::ENTER] = game::InputEvent::Type::ACCEPT;
        config.button_map.keyboard[engine::Input::Button::ESCAPE] = game::InputEvent::Type::RETURN;


        nlohmann::json audio = j["audio"];
        config.audio.master = audio["master"];
        config.audio.sfx = audio["sfx"];
        config.audio.music = audio["music"];

        config.show_framerate = j["show_framerate"];
        config.framerate_cap = j["framerate_cap"];
        config.framerate_limit = j["framerate_limit"];

        return config;
    }
} // game