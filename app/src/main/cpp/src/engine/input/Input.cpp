#include "Input.h"

namespace engine {
    engine::Input::Button stringToInputButton(const std::string &button) {
        static std::map<std::string, engine::Input::Button> button_map = {
                {"a",           engine::Input::A},
                {"b",           engine::Input::B},
                {"c",           engine::Input::C},
                {"d",           engine::Input::D},
                {"e",           engine::Input::E},
                {"f",           engine::Input::F},
                {"g",           engine::Input::G},
                {"h",           engine::Input::H},
                {"i",           engine::Input::I},
                {"j",           engine::Input::J},
                {"k",           engine::Input::K},
                {"l",           engine::Input::L},
                {"m",           engine::Input::M},
                {"n",           engine::Input::N},
                {"o",           engine::Input::O},
                {"p",           engine::Input::P},
                {"q",           engine::Input::Q},
                {"r",           engine::Input::R},
                {"s",           engine::Input::S},
                {"t",           engine::Input::T},
                {"u",           engine::Input::U},
                {"v",           engine::Input::V},
                {"w",           engine::Input::W},
                {"x",           engine::Input::X},
                {"y",           engine::Input::Y},
                {"z",           engine::Input::Z},

                {"left",        engine::Input::LEFT},
                {"right",       engine::Input::RIGHT},
                {"down",        engine::Input::DOWN},
                {"up",          engine::Input::UP},

                {"control",     engine::Input::CONTROL},
                {"shift",       engine::Input::SHIFT},
                {"tab",         engine::Input::TAB},
                {"escape",      engine::Input::ESCAPE},
                {"space",       engine::Input::SPACEBAR},
                {"enter",       engine::Input::ENTER},

                {"mouseleft",   engine::Input::MOUSELEFT},
                {"mouseright",  engine::Input::MOUSERIGHT},
                {"mousemiddle", engine::Input::MOUSEMIDDLE},
        };

        if (button_map.find(button) == button_map.end()) {
            throw std::runtime_error("Config file, unknown button \"" + button + "\"");
        }

        return button_map[button];
    }

    std::string stringToInputButton(const engine::Input::Button &button) {
        static std::map<engine::Input::Button, std::string> button_map = {
                {engine::Input::A,           "a"},
                {engine::Input::B,           "b"},
                {engine::Input::C,           "c"},
                {engine::Input::D,           "d"},
                {engine::Input::E,           "e"},
                {engine::Input::F,           "f"},
                {engine::Input::G,           "g"},
                {engine::Input::H,           "h"},
                {engine::Input::I,           "i"},
                {engine::Input::J,           "j"},
                {engine::Input::K,           "k"},
                {engine::Input::L,           "l"},
                {engine::Input::M,           "m"},
                {engine::Input::N,           "n"},
                {engine::Input::O,           "o"},
                {engine::Input::P,           "p"},
                {engine::Input::Q,           "q"},
                {engine::Input::R,           "r"},
                {engine::Input::S,           "s"},
                {engine::Input::T,           "t"},
                {engine::Input::U,           "u"},
                {engine::Input::V,           "v"},
                {engine::Input::W,           "w"},
                {engine::Input::X,           "x"},
                {engine::Input::Y,           "y"},
                {engine::Input::Z,           "z"},

                {engine::Input::LEFT,        "left"},
                {engine::Input::RIGHT,       "right"},
                {engine::Input::DOWN,        "down"},
                {engine::Input::UP,          "up"},
                {engine::Input::CONTROL,     "control"},
                {engine::Input::SHIFT,       "shift"},
                {engine::Input::TAB,         "tab"},
                {engine::Input::ESCAPE,      "escape"},
                {engine::Input::SPACEBAR,    "space"},
                {engine::Input::ENTER,       "enter"},
                {engine::Input::MOUSELEFT,   "mouseleft"},
                {engine::Input::MOUSERIGHT,  "mouseright"},
                {engine::Input::MOUSEMIDDLE, "mousemiddle"},
        };

        if (button_map.find(button) == button_map.end()) {
            throw std::runtime_error("Unable to map engine input button enum to string");
        }

        return button_map[button];
    }
} // engine