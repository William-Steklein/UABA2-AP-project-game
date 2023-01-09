#include "InAirState.h"
#include "game/entities/world/player/state/on-ground/IdleState.h"
#include "game/entities/world/player/state/wall-slide/WallSlideState.h"

namespace game {
    InAirState::InAirState(Player &state_machine, std::unique_ptr<IPlayerState> &state)
            : IPlayerState(state_machine, state), _h_movement(false) {}

    void InAirState::physicsUpdate(double t, float dt) {
        // gravity
        _state_machine._physics_component->applyGravityForce();

        // air movement
        if (_h_movement) {
            _state_machine._physics_component->applyHorizontalMovementForce(_state_machine.isFacingLeft());
        }

        // wall slide
        if (_state_machine.isFacingLeft() && _state_machine._left_wall_slide_ray->collided() ||
            !_state_machine.isFacingLeft() && _state_machine._right_wall_slide_ray->collided()) {
            set<WallSlideState>();
            return;
        }

        // standing
        if (_state_machine._standing_ray->collided()) {
            set<IdleState>();
            return;
        }

        IPlayerState::physicsUpdate(t, dt);
    }

    void InAirState::handleInput(const InputEvent &input) {
        if (input.type == InputEvent::Type::LEFT || input.type == InputEvent::Type::RIGHT) {
            _h_movement = (input.state == InputEvent::State::ENTERED || input.state == InputEvent::State::ACTIVE);
        }

        IPlayerState::handleInput(input);
    }
} // game