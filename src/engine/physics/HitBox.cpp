#include "HitBox.h"

namespace engine {
    HitBox::HitBox(const Vector2f &size, const Vector2f &offset)
            : _size(size), _offset(offset) {

    }

    void HitBox::update(double t, float dt) {
        
    }

    const Vector2f &HitBox::getSize() const {
        return _size;
    }

    void HitBox::setSize(const Vector2f &size) {
        _size = size;
    }

    Vector2f HitBox::getScaledSize() {
        return {_size.x * getTransform()->scale.x, _size.y * getTransform()->scale.y};
    }

    const Vector2f &HitBox::getOffset() const {
        return _offset;
    }

    void HitBox::setOffset(const Vector2f &offset) {
        _offset = offset;
    }

    bool HitBox::collides(const Vector2f &point) {
        Vector2f position = getTransform()->position;
        Vector2f size = getScaledSize();
        
        return point.x < position.x + size.x / 2 && point.x > position.x - size.x / 2 &&
               point.y < position.y + size.y / 2 && point.y > position.y - size.y / 2;
    }

    bool HitBox::collides(HitBox &other) {
        Vector2f position = getTransform()->position;
        Vector2f size = getScaledSize();
        Vector2f position_other = other.getTransform()->position;
        Vector2f size_other = other.getScaledSize();

        return position.x - size.x / 2 < position_other.x + size_other.x / 2 &&
               position.x + size.x / 2 > position_other.x - size_other.x / 2 &&
               position.y - size.y / 2 < position_other.y + size_other.y / 2 &&
               position.y + size.y / 2 > position_other.y - size_other.y / 2;
    }
} // engine