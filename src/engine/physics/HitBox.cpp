#include "HitBox.h"

namespace engine {
    HitBox::HitBox(const Vector2f &position, const Vector2f &size, const Vector2f &offset)
            : _size(size), _offset(offset) {
        setPosition(position);
    }

    const Vector2f &HitBox::getPosition() const {
        return _position;
    }

    void HitBox::setPosition(const Vector2f &position) {
        _position = position + _offset;
    }

    const Vector2f &HitBox::getSize() const {
        return _size;
    }

    void HitBox::setSize(const Vector2f &size) {
        _size = size;
    }

    const Vector2f &HitBox::getOffset() const {
        return _offset;
    }

    void HitBox::setOffset(const Vector2f &offset) {
        _offset = offset;
    }

    bool HitBox::collides(const Vector2f &point) const {
        return point.x < _position.x + _size.x / 2 && point.x > _position.x - _size.x / 2 &&
               point.y < _position.y + _size.y / 2 && point.y > _position.y - _size.y / 2;
    }

    bool HitBox::collides(const HitBox &other) const {
        return _position.x - _size.x / 2 < other._position.x + other._size.x / 2 &&
               _position.x + _size.x / 2 > other._position.x - other._size.x / 2 &&
               _position.y - _size.y / 2 < other._position.y + other._size.y / 2 &&
               _position.y + _size.y / 2 > other._position.y - other._size.y / 2;
    }
} // engine