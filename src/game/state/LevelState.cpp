#include "LevelState.h"
#include <engine/utils/file_io.h>

#include <utility>
#include <algorithm>

namespace game {
    void removeWhiteSpace(std::string &str) {
        std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
        str.erase(end_pos, str.end());
    }

    engine::Vector2f parseVector2f(const std::string &str) {
        size_t pos = str.find(',');
        if (pos > str.length()) {
            throw std::runtime_error("Unable to parse string to vector2f");
        }
        return {std::stof(str.substr(0, pos)), std::stof(str.substr(pos + 1))};
    }

    LevelState::LevelState(Game &game, std::string level_file_path)
            : WorldState(game), _level_file_path(std::move(level_file_path)) {

    }

    void LevelState::enter() {
        loadLevelFromFile();

        WorldState::enter();
    }

    void LevelState::loadLevelFromFile() {
        std::ifstream level_file = engine::read_file(_level_file_path);

        enum Part {
            UNDEFINED,
            META,
            ENTITIES,
        };

        Part header = UNDEFINED;

        std::string line;
        unsigned int line_count{0};
        while (std::getline(level_file, line)) {
            line_count++;

            if (line.empty() || line[0] == '#') {
                continue;
            }

            if (line[0] == '-') {
                std::string sub_line = line.substr(1);
                if (sub_line == "meta") {
                    header = META;
                } else if (sub_line == "entities") {
                    header = ENTITIES;
                }

                continue;
            }

            switch (header) {
                case UNDEFINED:
                    throw std::runtime_error("No header defined while parsing \"" + _level_file_path + "\"");

                case META:

                    break;

                case ENTITIES:
                    if (std::count(line.begin(), line.end(), ';') != 3) {
                        throw std::runtime_error("Unable to parse entity on line " + std::to_string(line_count));
                    }

                    std::string current_line = line;
                    removeWhiteSpace(current_line);
                    std::string sub_line;
                    size_t pos{0};

                    // entity id
                    pos = current_line.find(';');
                    sub_line = current_line.substr(0, pos);
                    unsigned int entity_id = std::stoul(sub_line);
                    current_line = current_line.substr(pos + 1);

//                    std::cout << entity_id << std::endl;

                    // position
                    pos = current_line.find(';');
                    sub_line = current_line.substr(0, pos);
                    engine::Vector2f position = parseVector2f(sub_line);
                    current_line = current_line.substr(pos + 1);

//                    std::cout << position << std::endl;

                    // size
                    pos = current_line.find(';');
                    sub_line = current_line.substr(0, pos);
                    engine::Vector2f size;
                    if (sub_line.length() != 0) {
                        size = parseVector2f(sub_line);
                    } else {
                        // todo: get default size
                    }

//                    std::cout << size << std::endl;

                    if (entity_id == 0) {
                        createPlayer(position);
                    } else if (entity_id == 1) {
                        createWall(position, size);
                    }

                    break;
            }
        }

        level_file.close();
    }
} // game