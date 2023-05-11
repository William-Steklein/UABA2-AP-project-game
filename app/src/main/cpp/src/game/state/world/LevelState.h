#ifndef GAME_ENGINE_LEVELSTATE_H
#define GAME_ENGINE_LEVELSTATE_H


#include "WorldState.h"

namespace game {

    class LevelState : public WorldState {
    public:
        LevelState(Game &state_machine, std::stack<std::unique_ptr<IGameState>> &states);

        ~LevelState() override = default;

        void enter() override;

        void reset() override;

        void graphicsUpdate(double t, float dt) override;

        void physicsUpdate(double t, float dt) override;

        void loadLevelData();

        void updateCollisions() override;

    private:
        std::shared_ptr<LevelData> _level_data;

        std::shared_ptr<Finish> _finish;
        bool _finished;

        void createFinish(const engine::Vector2f &position, const engine::Vector2f &size = {0.25, 0.25});

        void createDebugViewComponents() override;
    };

} // game

#endif //GAME_ENGINE_LEVELSTATE_H
