#ifndef GAME_ENGINE_LEVELDATA_H
#define GAME_ENGINE_LEVELDATA_H


#include <string>
#include <utility>
#include <vector>

#include "engine/math/Vector2f.h"

namespace game {

    struct LevelData {
        struct EntityData {
            EntityData() = default;

            EntityData(const engine::Vector2f &position_, const engine::Vector2f &size_)
                    : position(position_), size(size_) {};

            engine::Vector2f position;
            engine::Vector2f size;
        };

        struct TileData : public EntityData {
            TileData() : EntityData(), type(0) {}

            TileData(const engine::Vector2f &position_, const engine::Vector2f &size_,
                     unsigned int type_, bool animated_, std::string sprite_id_)
                    : EntityData(position_, size_), type(type_),
                      sprite_id(std::move(sprite_id_)) {}

            unsigned int type;
            std::string sprite_id;
        };

        LevelData() = default;

        std::string name;

        EntityData player;
        EntityData finish;
        std::vector<EntityData> walls;
        std::vector<TileData> tiles;
//        std::vector<EntityData> backgrounds;
    };

} // game

#endif //GAME_ENGINE_LEVELDATA_H
