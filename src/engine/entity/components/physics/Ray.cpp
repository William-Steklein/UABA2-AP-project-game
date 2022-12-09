#include "Ray.h"
#include "engine/math/math_utils.h"

namespace engine {
    Ray::Ray(const Vector2f &origin, const Vector2f &end)
            : _origin(origin), _end(end), _collided(false) {

    }

    Ray::Ray(const Vector2f &origin, const Vector2f &direction, float length)
            : _origin(origin), _end(origin + (direction * length)) {

    }

    void Ray::update(double t, float dt) {

    }

    const Vector2f &Ray::getOrigin() const {
        return _origin;
    }

    Vector2f Ray::getAbsoluteOrigin() {
        return getPosition() + _origin;
    }

    void Ray::setOrigin(const Vector2f &origin) {
        _origin = origin;
    }

    const Vector2f &Ray::getEnd() const {
        return _end;
    }

    Vector2f Ray::getAbsoluteEnd() {
        return getPosition() + _end;
    }

    void Ray::setEnd(const Vector2f &end) {
        _end = end;
    }

    bool Ray::collided() const {
        return _collided;
    }

    void Ray::setCollided(bool collided) {
        _collided = collided;
    }

    const Vector2f &Ray::getCollisionPoint() const {
        return _collision_point;
    }

    void Ray::setCollisionPoint(const Vector2f &collision_point) {
        _collision_point = collision_point;
    }

    void Ray::reset() {
        _collided = false;
        _collision_point.clear();
    }

    bool Ray::collides(const Vector2f &other_absolute_origin, const Vector2f &other_absolute_end,
                       bool set_collision_point) {
        Vector2f intersection1;
        Vector2f intersection2;
        bool is_collinear = false;

        Vector2f _absolute_origin = getAbsoluteOrigin();
        Vector2f _absolute_end = getAbsoluteEnd();

        bool collision = linesegmentIntersection(_absolute_origin, _absolute_end,
                                                 other_absolute_origin, other_absolute_end,
                                                 intersection1, intersection2, is_collinear);

        if (collision && set_collision_point) {
            Vector2f closest_intersection;
            if (is_collinear) {
                // check the closest intersection of 1 & 2
                if ((intersection1 - _absolute_origin).length() < (intersection2 - _absolute_origin).length()) {
                    closest_intersection = intersection1;
                } else {
                    closest_intersection = intersection2;
                }
            } else {
                closest_intersection = intersection1;
            }

            // check the closest point of the closest intersection and previous intersection;
            if (_collided) {
                if ((closest_intersection - _absolute_origin).length() <
                    (_collision_point - _absolute_origin).length()) {
                    _collision_point = closest_intersection;
                }
                _collided = true;
            } else {
                _collision_point = closest_intersection;
                _collided = true;
            }
        }

        return collision;
    }

    bool Ray::collides(Ray &other, bool set_collision_point) {
        if (collides(other.getAbsoluteOrigin(), other.getAbsoluteOrigin(), set_collision_point)) {
            setCollided(true);
            other.setCollided(true);
            return true;
        }
        return false;
    }

    bool Ray::collides(HitBox &other, bool set_collision_point) {
        if (set_collision_point) {
            Vector2f h0 = other.getTransform()->position - other.getSize() / 2;
            Vector2f h1 = {h0.x + other.getSize().x, h0.y};
            Vector2f h2 = {h0.x + other.getSize().x, h0.y + other.getSize().y};
            Vector2f h3 = {h0.x, h0.y + other.getSize().y};

            collides(h0, h1, set_collision_point);
            collides(h1, h2, set_collision_point);
            collides(h2, h3, set_collision_point);
            collides(h3, h0, set_collision_point);
        }

        if (other.collides(getAbsoluteOrigin()) || other.collides(getAbsoluteEnd())) {
            setCollided(true);
            return true;
        }

        return false;
    }
} // engine