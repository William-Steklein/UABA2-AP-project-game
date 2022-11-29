#include "UIEntity.h"

namespace engine {
    UIEntity::UIEntity(engine::Transform transform, const std::vector<std::shared_ptr<IComponent>> &components)
            : Entity(std::move(transform), components) {

    }

    void UIEntity::update(double t, float dt) {
        Entity::update(t, dt);

        for (const auto &child: _children) {
            child->update(t, dt);
        }
    }

    void UIEntity::setPosition(const engine::Vector2f &position) {
        for (const auto &child: _children) {
            if (child->_relative_positioning) {
                child->move(position - getPosition());
            }
        }

        Entity::setPosition(position);
    }

    void UIEntity::setRelativePosition(const engine::Vector2f &position) {
        if (_relative_positioning && hasParent()) {
            std::shared_ptr<Entity> parent = _parent.lock();
            setPosition(parent->getPosition() + position);
        }
    }

    const std::weak_ptr<UIEntity> &UIEntity::getParent() const {
        return _parent;
    }

    void UIEntity::setParent(const std::weak_ptr<UIEntity> &parent) {
        _parent = parent;
    }

    bool UIEntity::hasParent() const {
        return !_parent.expired();
    }

    const std::vector<std::shared_ptr<UIEntity>> &UIEntity::getChildren() const {
        return _children;
    }

    void UIEntity::setChildren(const std::vector<std::shared_ptr<UIEntity>> &children) {
        _children = children;
    }

    void UIEntity::addChild(const std::shared_ptr<UIEntity> &child, const std::weak_ptr<UIEntity> &parent,
                            bool relative_positioning) {
        child->_parent = parent;
        child->_relative_positioning = relative_positioning;
        if (relative_positioning) {
            child->setRelativePosition(child->getPosition());
        }
        _children.push_back(child);
    }

    void UIEntity::addChildren(const std::vector<std::shared_ptr<UIEntity>> &children,
                               const std::weak_ptr<UIEntity> &parent, bool relative_positioning) {
        for (const auto &child: children) {
            addChild(child, parent, relative_positioning);
        }
    }

    bool UIEntity::hasChildren() const {
        return !_children.empty();
    }

    bool UIEntity::isRelativePositioning() const {
        return _relative_positioning;
    }

    void UIEntity::setRelativePositioning(bool relativePositioning) {
        _relative_positioning = relativePositioning;
    }
} // engine