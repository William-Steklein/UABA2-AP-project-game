#ifndef GAME_ENGINE_WORLDSTATE_H
#define GAME_ENGINE_WORLDSTATE_H


#include "game/state/IGameState.h"
#include "game/entities/world/player/Player.h"
#include "game/entities/world/terrain/Wall.h"
#include "game/entities/world/finish/Finish.h"
#include "game/entities/world/terrain/Tile.h"

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
        std::vector<std::shared_ptr<Tile>> _tiles;

        std::vector<std::shared_ptr<engine::IViewComponent>> _debug_components;
        bool _debug_view_visibility;

        std::shared_ptr<engine::Entity> _fps_counter;
        std::shared_ptr<engine::ITextBoxComponent> _fps_counter_text;

        void createPlayer(const engine::Vector2f &position, const engine::Vector2f &size);

        void cameraFollowPlayer();

        void createWall(const engine::Vector2f &position, const engine::Vector2f &size);

        void createTile(const engine::Vector2f &position, const engine::Vector2f &size,
                        unsigned int layer, const std::string &sprite_id);

        virtual void updateCollisions();

        virtual void createDebugViewComponents();

        virtual void updateDebugViewComponents(double t, float dt);

        void toggleDebugViewVisibility();

        void updateFpsCounterText();
    };

}


#endif //GAME_ENGINE_WORLDSTATE_H
