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
            throw std::runtime_error("Line \"" + line + " \" does not contain ';'");
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
                    if (std::count(line.begin(), line.end(), ';') < 2) {
                        throw std::runtime_error("Unable to parse entity on line " + std::to_string(line_count));
                    }

                    removeWhiteSpace(line);

                    std::vector<std::string> line_segments = segmentEntityLine(line);

                    unsigned int entity_id = parseUnsignedIntString(line_segments[0]);
                    if (entity_id == 3) {
                        LevelData::TileData entity_data{};

                        if (line_segments.size() != 4 && line_segments.size() != 5) {
                            throw std::runtime_error("Unable to parse entity line");
                        }

                        entity_data.position = parseVector2fString(line_segments[3]);

                        if (line_segments.size() == 6) {
                            entity_data.size = parseVector2fString(line_segments[4]);
                        } else {
                            entity_data.size = constants::size::tile;
                        }

                        entity_data.type = parseUnsignedIntString(line_segments[1]);

                        entity_data.sprite_id = line_segments[2];

                        level_data->tiles.push_back(entity_data);

                    } else {
                        LevelData::EntityData entity_data{};

                        if (line_segments.size() != 2 && line_segments.size() != 3) {
                            throw std::runtime_error("Unable to parse entity line");
                        }

                        entity_data.position = parseVector2fString(line_segments[1]);

                        bool default_size{false};

                        if (line_segments.size() == 3) {
                            entity_data.size = parseVector2fString(line_segments[2]);
                        } else {
                            default_size = true;
                        }

                        switch (entity_id) {
                            case 0:
                                if (default_size) {
                                    entity_data.size = constants::size::player;
                                }

                                level_data->player = entity_data;
                                break;

                            case 1:
                                if (default_size) {
                                    entity_data.size = constants::size::finish;
                                }

                                level_data->finish = entity_data;
                                break;

                            case 2:
                                if (default_size) {
                                    entity_data.size = constants::size::wall;
                                }

                                level_data->walls.push_back(entity_data);
                                break;

                            default:
                                break;
                        }
                    }

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