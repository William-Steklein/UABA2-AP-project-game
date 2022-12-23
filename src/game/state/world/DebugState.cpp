#include "DebugState.h"
#include "game/constants/constants.h"
#include "game/entities/player/state/IPlayerState.h"

namespace game {
    void DebugState::enter() {
        generateBackground({0, 0}, {20, 20}, {0.5, 0.5});

        _player = std::shared_ptr<Player>(new Player(
                {{0, 1}, {1, 1}, 0},
                _state_machine.getViewComponentCreator()->createAnimatedSprite(
                        constants::player::view_size, 1, false, "adventurer")
        ));

        _entities.insert(_player);

        createWall({-0.5, 0.25}, {0.25, 0.25});
        createWall({-1, 0.5}, {0.25, 0.25});

        createWall({2, 2}, {0.25, 4});
        createWall({2.75, 2}, {0.25, 4});


        createWall({0, -0.5}, {10, 0.25});

        game::WorldState::enter();
    }

    void DebugState::generateBackground(const engine::Vector2f &position,
                                        const engine::Vector2f &size, const engine::Vector2f &entity_size) {
        engine::Vector2f total_size = {std::ceil(size.x / entity_size.x) * entity_size.x,
                                       std::ceil(size.y / entity_size.y) * entity_size.y};
        engine::Vector2f origin = (position - total_size / 2) + entity_size / 2;

        int x_tile_count = std::ceil(size.x / entity_size.x);
        int y_tile_count = std::ceil(size.y / entity_size.y);
        for (int y_count = 0; y_count < y_tile_count; y_count++) {
            for (int x_count = 0; x_count < x_tile_count; x_count++) {
                engine::Vector2f entity_position = {origin.x + static_cast<float>(x_count) * entity_size.x,
                                                    origin.y + static_cast<float>(y_count) * entity_size.y};

                std::shared_ptr<engine::Entity> background = std::make_shared<engine::Entity>(engine::Entity(
                        {entity_position, {1, 1}, 0},
                        {_state_machine.getViewComponentCreator()->createSprite(
                                entity_size, 0, false, "pr_background"),}
                ));

                _entities.insert(background);
            }
        }
    }


} // game