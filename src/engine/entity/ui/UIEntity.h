#ifndef GAME_ENGINE_UIENTITY_H
#define GAME_ENGINE_UIENTITY_H


#include "engine/entity/Entity.h"

namespace engine {

    class UIEntity : public Entity {
    public:
        UIEntity(Transform transform, const std::vector<std::shared_ptr<IComponent>> &components = {});

        ~UIEntity() override = default;

        void graphicsUpdate(double t, float dt) override;

        void setPosition(const engine::Vector2f &position) override;

        void setRelativePosition(const engine::Vector2f &position);

        const std::weak_ptr<UIEntity> &getParent() const;

        void setParent(const std::weak_ptr<UIEntity> &parent);

        bool hasParent() const;

        const std::vector<std::shared_ptr<UIEntity>> &getChildren() const;

        void setChildren(const std::vector<std::shared_ptr<UIEntity>> &children);

        void addChild(const std::shared_ptr<UIEntity> &child, const std::weak_ptr<UIEntity> &parent,
                      bool relative_positioning = true);

        void addChildren(const std::vector<std::shared_ptr<UIEntity>> &children, const std::weak_ptr<UIEntity> &parent,
                         bool relative_positioning = true);

        bool hasChildren() const;

        bool isRelativePositioning() const;

        void setRelativePositioning(bool relativePositioning);

    private:
        std::weak_ptr<UIEntity> _parent;
        std::vector<std::shared_ptr<UIEntity>> _children;

        bool _relative_positioning;
    };

} // engine

#endif //GAME_ENGINE_UIENTITY_H
