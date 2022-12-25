#include "UIEntity.h"

namespace engine {
    UIEntity::UIEntity(engine::Transform transform, const std::vector<std::shared_ptr<IComponent>> &components)
            : Entity(std::move(transform), components) {

    }

    void UIEntity::graphicsUpdate(double t, float dt) {
        Entity::graphicsUpdate(t, dt);

        for (const auto &child: _children) {
            child->graphicsUpdate(t, dt);
        }

        for (auto child_it = _weak_children.begin(); child_it != _weak_children.end();) {
            if ((*child_it).expired()) {
                child_it = _weak_children.erase(child_it);
            } else {
                child_it->lock()->graphicsUpdate(t, dt);

                child_it++;
            }
        }
    }

    void UIEntity::setPosition(const engine::Vector2f &position) {
        for (const auto &child: _children) {
            if (child->_relative_positioning) {
                child->move(position - getPosition());
            }
        }

        for (auto child_it = _weak_children.begin(); child_it != _weak_children.end();) {
            if ((*child_it).expired()) {
                child_it = _weak_children.erase(child_it);
            } else {
                child_it->lock()->move(position - getPosition());

                child_it++;
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

    std::vector<std::shared_ptr<UIEntity>> UIEntity::getChildren() {
        std::vector<std::shared_ptr<UIEntity>> children = _children;

        for (auto child_it = _weak_children.begin(); child_it != _weak_children.end();) {
            if ((*child_it).expired()) {
                child_it = _weak_children.erase(child_it);
            } else {
                children.push_back(child_it->lock());

                child_it++;
            }
        }

        return children;
    }

    void UIEntity::addChild(const std::shared_ptr<UIEntity> &child, const std::weak_ptr<UIEntity> &parent,
                            bool relative_positioning) {
        _linkChild(child, parent, relative_positioning);
        _children.push_back(child);
    }

    void UIEntity::addWeakChild(const std::weak_ptr<UIEntity> &child, const std::weak_ptr<UIEntity> &parent,
                                bool relative_positioning) {
        if (child.expired()) return;
        _linkChild(child.lock(), parent, relative_positioning);
        _weak_children.push_back(child);
    }

    bool UIEntity::hasChildren() {
        return !getChildren().empty();
    }

    bool UIEntity::isRelativePositioning() const {
        return _relative_positioning;
    }

    void UIEntity::setRelativePositioning(bool relativePositioning) {
        _relative_positioning = relativePositioning;
    }

    void UIEntity::_linkChild(const std::shared_ptr<UIEntity> &child, const std::weak_ptr<UIEntity> &parent,
                              bool relative_positioning) {
        child->_parent = parent;
        child->_relative_positioning = relative_positioning;
        if (relative_positioning) {
            child->setRelativePosition(child->getPosition());
        }
        child->graphicsUpdate(0,0);
    }
} // engine