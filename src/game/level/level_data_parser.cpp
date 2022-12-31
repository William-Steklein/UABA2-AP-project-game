#include "level_data_parser.h"
#include "engine/utils/file_io.h"

namespace game {
    void removeWhiteSpace(std::string &str) {
        std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
        str.erase(end_pos, str.end());
    }

    inline bool parseBoolString(const std::string &str) {
        try {
            return static_cast<bool>(std::stoi(str));
        } catch (...) {
            throw std::runtime_error("Unable to parse bool string \"" + str + "\"");
        }
    }

    inline float parseFloatString(const std::string &str) {
        try {
            return std::stof(str);
        } catch (...) {
            throw std::runtime_error("Unable to parse float string \"" + str + "\"");
        }
    }

    inline unsigned int parseUnsignedIntString(const std::string &str) {
        try {
            return std::stol(str);
        } catch (...) {
            throw std::runtime_error("Unable to parse unsigned int string \"" + str + "\"");
        }
    }

    inline engine::Vector2f parseVector2fString(const std::string &str) {
        size_t pos = str.find(',');
        if (pos > str.length()) {
            throw std::runtime_error("Unable to parse vector2f string \"" + str + "\"");
        }
        return {std::stof(str.substr(0, pos)), std::stof(str.substr(pos + 1))};
    }

    std::vector<std::string> segmentEntityLine(const std::string &line) {
        if (std::count(line.begin(), line.end(), ';') == 0) {
            throw std::runtime_error("Entity line \"" + line + " \" does not contain ';'");
        }

        std::vector<std::string> segments;

        std::string current_line = line;
        size_t pos{0};

        while (!current_line.empty()) {
            pos = current_line.find(';');

            segments.push_back(current_line.substr(0, pos));

            current_line = current_line.substr(pos + 1);
        }

        return segments;
    }

    std::pair<std::string, std::string> parseMetaLine(const std::string &line) {
        if (std::count(line.begin(), line.end(), '=') == 0) {
            throw std::runtime_error("Meta line \"" + line + " \" does not contain '='");
        }

        size_t pos = line.find('=');

        return {line.substr(0, pos), line.substr(pos + 1)};
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

            removeWhiteSpace(line);

            switch (header) {
                case UNDEFINED:
                    throw std::runtime_error("No header defined while parsing \"" + filepath + "\"");

                case META:
                    {
                        std::pair<std::string, std::string> meta_pair = parseMetaLine(line);

                        if (meta_pair.first == "origin") {
                            level_data->origin = parseVector2fString(meta_pair.second);
                        } else if (meta_pair.first == "limit") {
                            level_data->limit = parseVector2fString(meta_pair.second);
                        }
                    }

                    break;

                case ENTITIES:
                    if (std::count(line.begin(), line.end(), ';') < 3) {
                        throw std::runtime_error("Unable to parse entity on line " + std::to_string(line_count));
                    }

                    std::vector<std::string> line_segments = segmentEntityLine(line);

                    unsigned int entity_id = parseUnsignedIntString(line_segments[0]);

                    engine::Vector2f position = parseVector2fString(line_segments[1]);

                    bool default_size{false};
                    engine::Vector2f size;
                    if (!line_segments[2].empty()) {
                        size = parseVector2fString(line_segments[2]);
                    } else {
                        switch (entity_id) {
                            case 0:
                                size = constants::size::player;
                                break;

                            case 1:
                                size = constants::size::finish;
                                break;

                            case 2:
                                size = constants::size::wall;
                                break;

                            case 3:
                                size = constants::size::tile;
                                break;

                            default:
                                break;
                        }
                    }

                    switch (entity_id) {
                        case 2:
                            // wall
                            level_data->walls.emplace_back(position,
                                                           size,
                                                           parseBoolString(line_segments[3]));
                            break;

                        case 3:
                            // tile
                            level_data->tiles.emplace_back(position,
                                                           size,
                                                           parseUnsignedIntString(line_segments[3]),
                                                           line_segments[4]);
                            break;

                        case 0:
                            // player
                            level_data->player = LevelData::EntityData(position, size);
                            break;

                        case 1:
                            level_data->finish = LevelData::EntityData(position, size);
                            break;

                        default:
                            break;
                    }
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