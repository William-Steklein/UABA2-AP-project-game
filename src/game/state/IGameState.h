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
        virtual ~IGameState() = default;

        virtual void enter(Game &game) {};

        virtual void exit(Game &game) {};

        virtual void reset(Game &game);

        virtual void update(Game &game, double t, float dt);

        virtual void physicsUpdate(Game &game, double t, float dt);

        virtual void handleInput(Game &game, const InputEvent &input) {};

    protected:
        std::set<std::shared_ptr<engine::Entity>> _entities;
        std::set<std::shared_ptr<engine::Entity>> _physics_entities;
    };

} // game

#endif //GAME_ENGINE_IGAMESTATE_H
