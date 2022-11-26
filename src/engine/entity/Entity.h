#ifndef GAME_ENGINE_ENTITY_H
#define GAME_ENGINE_ENTITY_H


#include <vector>
#include <memory>
#include <utility>
#include <algorithm>

#include "engine/entity/components/Transform.h"
#include "engine/entity/components/IComponent.h"

namespace engine {

    class Entity {
    public:
        Entity(Transform transform);

        ~Entity() = default;

        virtual void update(double t, float dt);

        const Transform &getTransform() const;

        void setTransform(const Transform &transform);

        const Vector2f &getPosition() const;

        void setPosition(const Vector2f &position);

        const Vector2f &getScale() const;

        void setScale(const Vector2f &scale);

        const float &getRotation() const;

        void setRotation(const float &rotation);

        void addComponent(std::shared_ptr<IComponent> component);

        void removeComponent(const std::shared_ptr<IComponent>& component);

    protected:
        Transform _transform;

        std::vector<std::shared_ptr<IComponent>> _components;

        static void checkComponent(const std::shared_ptr<IComponent> &component);
    };

} // engine

#endif //GAME_ENGINE_ENTITY_H
