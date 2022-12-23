#ifndef GAME_ENGINE_DEBUGSTATE_H
#define GAME_ENGINE_DEBUGSTATE_H


#include "game/state/WorldState.h"

namespace game {

    class DebugState : public WorldState {
    public:
        using WorldState::WorldState;

        ~DebugState() override = default;

        void enter() override;

    private:
        void generateBackground(const engine::Vector2f &position, const engine::Vector2f &size,
                                const engine::Vector2f &entity_size);
    };

} // game


#endif //GAME_ENGINE_DEBUGSTATE_H
