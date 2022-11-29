#ifndef GAME_ENGINE_IGAMESTATE_H
#define GAME_ENGINE_IGAMESTATE_H


#include <memory>
#include <set>

#include <engine/entity/Entity.h>

#include "game/input/InputEvent.h"

namespace game {

    class Game;

    class IGameState {
    public:
        virtual ~IGameState() = default;

        virtual void enter(Game &game) = 0;

        virtual std::shared_ptr<IGameState> update(Game &game, double t, float dt);

        virtual std::shared_ptr<IGameState> physicsUpdate(Game &game, double t, float dt);

        virtual std::shared_ptr<IGameState> handleInput(Game &game, const InputEvent &input) = 0;

    protected:
        std::set<std::shared_ptr<engine::Entity>> _entities;
        std::set<std::shared_ptr<engine::Entity>> _physics_entities;
    };

} // game

#endif //GAME_ENGINE_IGAMESTATE_H
