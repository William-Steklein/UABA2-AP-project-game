#ifndef GAME_ENGINE_WORLDSTATE_H
#define GAME_ENGINE_WORLDSTATE_H


#include "game/state/IGameState.h"
#include "game/entities/world/player/Player.h"
#include "game/entities/world/terrain/Wall.h"
#include "game/entities/world/finish/Finish.h"

namespace game {

    class WorldState : public IGameState {
    public:
        WorldState(Game &state_machine, std::stack<std::unique_ptr<IGameState>> &states);

        ~WorldState() override = default;

        void enter() override;

        void reset() override;

        void physicsUpdate(double t, float dt) override;

        void graphicsUpdate(double t, float dt) override;

        void handleInput(const InputEvent &input) override;

    protected:
        std::shared_ptr<Player> _player;
        std::vector<std::shared_ptr<Wall>> _walls;

        std::vector<std::shared_ptr<engine::IViewComponent>> _debug_components;
        bool _debug_view_visibility;

        std::shared_ptr<engine::Entity> _fps_counter;
        std::shared_ptr<engine::ITextBoxComponent> _fps_counter_text;

        void createPlayer(const engine::Vector2f &position);

        void cameraFollowPlayer();

        void createWall(const engine::Vector2f &position, const engine::Vector2f &size = {0.25, 0.25});

        virtual void updateCollisions();

        virtual void createDebugViewComponents();

        virtual void updateDebugViewComponents(double t, float dt);

        void toggleDebugViewVisibility();

        void updateFpsCounterText();
    };

}


#endif //GAME_ENGINE_WORLDSTATE_H
