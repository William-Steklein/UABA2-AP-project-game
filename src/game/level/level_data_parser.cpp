#include "level_data_parser.h"
#include "engine/utils/file_io.h"

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

    std::shared_ptr<LevelData> levelDataParser(const std::string &filepath) {
        std::shared_ptr<LevelData> level_data = std::make_shared<LevelData>();

        std::ifstream level_file = engine::read_file(filepath);

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
                    throw std::runtime_error("No header defined while parsing \"" + filepath + "\"");

                case META:

                    break;

                case ENTITIES:
                    if (std::count(line.begin(), line.end(), ';') != 3) {
                        throw std::runtime_error("Unable to parse entity on line " + std::to_string(line_count));
                    }

                    LevelData::EntityData entity_data{};

                    std::string current_line = line;
                    removeWhiteSpace(current_line);
                    std::string sub_line;
                    size_t pos{0};

                    // entity id
                    pos = current_line.find(';');

                    sub_line = current_line.substr(0, pos);
                    entity_data.id = std::stoul(sub_line);

                    current_line = current_line.substr(pos + 1);

                    // position
                    pos = current_line.find(';');

                    sub_line = current_line.substr(0, pos);
                    entity_data.position = parseVector2f(sub_line);

                    current_line = current_line.substr(pos + 1);

                    // size
                    pos = current_line.find(';');
                    sub_line = current_line.substr(0, pos);
                    engine::Vector2f size;
                    if (sub_line.length() != 0) {
                        entity_data.size = parseVector2f(sub_line);
                    } else {
                        // todo: get default size
                    }

                    level_data->entity_data.push_back(entity_data);

                    break;
            }
        }

        level_file.close();

        return level_data;
    }

    std::vector<std::shared_ptr<LevelData>> levelsDataParser(const std::string &filepath) {
        std::vector<std::shared_ptr<LevelData>> levels_data;

        nlohmann::json j = engine::loadJsonFromFile(filepath);

        for (const auto &level_filepath: j["levels"]) {
            levels_data.push_back(levelDataParser(level_filepath));
        }

        return levels_data;
    }
} // game