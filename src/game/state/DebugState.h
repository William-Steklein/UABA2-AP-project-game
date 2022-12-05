#ifndef GAME_ENGINE_DEBUGSTATE_H
#define GAME_ENGINE_DEBUGSTATE_H


#include "game/state/IGameState.h"
#include "game/entities/player/Player.h"
#include "game/entities/Wall.h"

namespace game {

    class DebugState : public IGameState {
    public:
        DebugState(Game &game);

        ~DebugState() override = default;

        void enter() override;

        virtual void resume();

        void reset() override;

        void physicsUpdate(double t, float dt) override;

        void graphicsUpdate(double t, float dt) override;

        void handleInput(const game::InputEvent &input) override;

        void generateBackground(const engine::Vector2f &position, const engine::Vector2f &size,
                                const engine::Vector2f &entity_size);

        void createWall(const engine::Vector2f &position, float size = 0.5);

        void updateCollisions();

    private:
        std::shared_ptr<Player> _player;
        std::vector<std::shared_ptr<Wall>> _walls;
    };

} // game


#endif //GAME_ENGINE_DEBUGSTATE_H
