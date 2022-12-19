#ifndef GAME_ENGINE_LEVELDATA_H
#define GAME_ENGINE_LEVELDATA_H


#include <string>
#include <vector>

#include "engine/math/Vector2f.h"

namespace game {

    struct LevelData {
        struct EntityData {
            EntityData() : id(0) {

            }

            EntityData(unsigned int id_, const engine::Vector2f &position_, const engine::Vector2f &size_)
                    : id(id_), position(position_), size(size_) {

            };

            unsigned int id;
            engine::Vector2f position;
            engine::Vector2f size;
        };

        LevelData() = default;

        std::string name;
        std::vector<EntityData> entity_data;
    };

} // game

#endif //GAME_ENGINE_LEVELDATA_H
