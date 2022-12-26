#ifndef GAME_ENGINE_PLAYER_H
#define GAME_ENGINE_PLAYER_H


#include "engine/entity/Entity.h"
#include "engine/entity/components/view/sprite/IAnimatedSpriteComponent.h"
#include "engine/entity/components/view/shape/IShapeComponent.h"
#include "engine/entity/components/physics/Ray.h"

#include "game/input/InputEvent.h"
#include "PlayerPhysicsComponent.h"

namespace game {

    class IPlayerState;

    class Player : public engine::Entity {
    public:
        enum Direction {
            LEFT,
            RIGHT,
        };

        std::shared_ptr<engine::IAnimatedSpriteComponent> _animated_sprite;
        std::shared_ptr<PlayerPhysicsComponent> _physics_component;

        std::shared_ptr<engine::Ray> _standing_ray;
        std::shared_ptr<engine::Ray> _left_wall_slide_ray;
        std::shared_ptr<engine::Ray> _right_wall_slide_ray;

        Player(engine::Transform transform,
               std::shared_ptr<engine::IAnimatedSpriteComponent> animated_sprite);

        ~Player() override = default;

        void physicsUpdate(double t, float dt) override;

        void graphicsUpdate(double t, float dt) override;

        void handleInput(const InputEvent &input);

        void updateDirection(Direction direction);

        bool isFacingLeft();

    private:
        std::unique_ptr<IPlayerState> _state;
        Direction _direction;

        void createHitBoxAndRays();
    };

} // game

#endif //GAME_ENGINE_PLAYER_H
