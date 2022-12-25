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

        std::vector<std::shared_ptr<UIEntity>> getChildren();

        void addChild(const std::shared_ptr<UIEntity> &child, const std::weak_ptr<UIEntity> &parent,
                      bool relative_positioning = true);

        void addWeakChild(const std::weak_ptr<UIEntity> &child, const std::weak_ptr<UIEntity> &parent,
                          bool relative_positioning = true);

        bool hasChildren();

        bool isRelativePositioning() const;

        void setRelativePositioning(bool relativePositioning);

    private:
        std::weak_ptr<UIEntity> _parent;
        std::vector<std::shared_ptr<UIEntity>> _children;
        std::vector<std::weak_ptr<UIEntity>> _weak_children;

        bool _relative_positioning;

        static inline void _linkChild(const std::shared_ptr<UIEntity> &child, const std::weak_ptr<UIEntity> &parent,
                                      bool relative_positioning = true);
    };

} // engine

#endif //GAME_ENGINE_UIENTITY_H
