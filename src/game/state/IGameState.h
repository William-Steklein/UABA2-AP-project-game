#ifndef GAME_ENGINE_IGAMESTATE_H
#define GAME_ENGINE_IGAMESTATE_H


#include <memory>
#include <set>

#include <engine/entity/Entity.h>

#include "game/Game.h"
#include "game/input/InputEvent.h"

namespace game {
    class IGameState {
    public:
        IGameState(Game &game);

        virtual ~IGameState() = default;

        virtual void enter() {};

        virtual void exit() {};

        virtual void reset();

        virtual void physicsUpdate(double t, float dt);

        virtual void graphicsUpdate(double t, float dt);

        virtual void handleInput(const InputEvent &input) {};

    protected:
        Game &_game;

        std::set<std::shared_ptr<engine::Entity>> _entities;
    };

} // game

#endif //GAME_ENGINE_IGAMESTATE_H
