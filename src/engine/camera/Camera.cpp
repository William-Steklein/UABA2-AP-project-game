#include "Camera.h"

namespace engine {
    Camera::Camera() : Camera({0, 0, 0, 0}) {}

    Camera::Camera(float left, float right, float bottom, float top)
            : _boundaries({-1, 1, -1, 1}), _screen_boundaries({left, right, bottom, top}),
              _sub_screen_boundaries({left, right, bottom, top}) {

    }

    const Vector2f &Camera::getPosition() const {
        return _position;
    }

    void Camera::setPosition(const Vector2f &position) {
        _position = position;
    }

    float Camera::getWidth() const {
        return _boundaries.x_max - _boundaries.x_min;
    }

    float Camera::getHeight() const {
        return _boundaries.y_max - _boundaries.y_min;
    }

    float Camera::getScreenWidth() const {
        return _screen_boundaries.x_max - _screen_boundaries.x_min;
    }

    float Camera::getScreenHeight() const {
        return _screen_boundaries.y_max - _screen_boundaries.y_min;
    }

    float Camera::getSubscreenWidth() const {
        return _sub_screen_boundaries.x_max - _sub_screen_boundaries.x_min;
    }

    float Camera::getSubscreenHeight() const {
        return _sub_screen_boundaries.y_max - _sub_screen_boundaries.y_min;
    }

    Vector2f Camera::projectCoordWorldToSubScreen(const Vector2f &coord) const {
        float alpha_x = (coord.x - _boundaries.x_min) / getWidth();
        float alpha_y = (coord.y - _boundaries.y_min) / getHeight();

        return {lerp(_sub_screen_boundaries.x_min, _sub_screen_boundaries.x_max, alpha_x),
                lerp(_sub_screen_boundaries.y_min, _sub_screen_boundaries.y_max, alpha_y)};
    }

    Vector2f Camera::projectSizeWorldToSubScreen(const Vector2f &size) const {
        return {std::abs(getSubscreenWidth()) / getWidth() * size.x,
                std::abs(getSubscreenHeight()) / getHeight() * size.y};
    }
} // engine