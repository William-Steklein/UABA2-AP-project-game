#ifndef GAME_ENGINE_ENTITY_H
#define GAME_ENGINE_ENTITY_H


#include <vector>
#include <memory>
#include <utility>
#include <algorithm>

#include "Transform.h"
#include "engine/entity/components/IComponent.h"

namespace engine {

    class Entity {
    public:
        Entity(Transform transform, const std::vector<std::shared_ptr<IComponent>> &components = {});

        virtual ~Entity() = default;

        virtual void physicsUpdate(double t, float dt);

        virtual void graphicsUpdate(double t, float dt);

        const std::shared_ptr<Transform> &getTransform() const;

        const Vector2f &getPosition() const;

        virtual void setPosition(const Vector2f &position);

        void move(const Vector2f &vector);

        const Vector2f &getScale() const;

        virtual void setScale(const Vector2f &scale);

        void scale(const Vector2f &scale);

        const float &getRotation() const;

        virtual void setRotation(const float &rotation);

        void rotate(float rotation);

        void addComponent(std::shared_ptr<IComponent> component, bool physics = false);

        void addComponents(const std::vector<std::shared_ptr<IComponent>> &components, bool physics = false);

    protected:
        std::shared_ptr<Transform> _transform;

        std::vector<std::shared_ptr<IComponent>> _components_physics;
        std::vector<std::shared_ptr<IComponent>> _components_graphics;

        static void checkComponent(const std::shared_ptr<IComponent> &component);
    };

} // engine

#endif //GAME_ENGINE_ENTITY_H
