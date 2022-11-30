#include "Camera.h"

namespace engine {
    Camera::Camera() : Camera({0, 0, 0, 0}) {}

    Camera::Camera(float left, float right, float bottom, float top)
            : _position(0, 0),
              _boundaries({-1.5, 1.5, -1, 1}), _screen_boundaries({left, right, bottom, top}),
              _sub_screen_aspect_ratio({3, 2}), _sub_screen_boundaries({left, right, bottom, top}) {
        if (getWidth() == 0 || getHeight() == 0) {
            throw std::runtime_error("Invalid camera boundaries");
        } else if (getScreenWidth() == 0 || getScreenHeight() == 0) {
            throw std::runtime_error("Invalid screen boundaries");
        }

        updateSubScreenResolution();
    }

    const Vector2f &Camera::getPosition() const {
        return _position;
    }

    void Camera::setPosition(const Vector2f &position) {
        _position = position;
    }

    void Camera::move(const engine::Vector2f &vector) {
        _position = _position + vector;
    }

    void Camera::reset() {
        _position = {0, 0};
    }

    void Camera::setScreenBoundaries(float left, float right, float bottom, float top) {
        _screen_boundaries = {left, right, bottom, top};
        updateSubScreenResolution();
    }

    const Camera::ViewBoundaries &Camera::getScreenBoundaries() const {
        return _screen_boundaries;
    }

    float Camera::getWidth() const {
        return std::abs(_boundaries.x_max - _boundaries.x_min);
    }

    float Camera::getHeight() const {
        return std::abs(_boundaries.y_max - _boundaries.y_min);
    }

    float Camera::getScreenWidth() const {
        return std::abs(_screen_boundaries.x_max - _screen_boundaries.x_min);
    }

    float Camera::getScreenHeight() const {
        return std::abs(_screen_boundaries.y_max - _screen_boundaries.y_min);
    }

    float Camera::getSubScreenWidth() const {
        return std::abs(_sub_screen_boundaries.x_max - _sub_screen_boundaries.x_min);
    }

    float Camera::getSubScreenHeight() const {
        return std::abs(_sub_screen_boundaries.y_max - _sub_screen_boundaries.y_min);
    }

    std::tuple<Vector2f, Vector2f, Vector2f> Camera::getSidebarData() const {
        return {_sidebar_size, _sidebar_1_position, _sidebar_2_position};
    }

    void Camera::updateSubScreenResolution() {
        Vector2f new_sub_screen_resolution;
        _sub_screen_boundaries = _screen_boundaries;

        // aspect ratio screen
        float ar_s = getScreenWidth() / getScreenHeight();
        // aspect ratio sub screen (i -> image)
        float ar_i = _sub_screen_aspect_ratio.x / _sub_screen_aspect_ratio.y;

        if (ar_s > ar_i) {
            new_sub_screen_resolution = {std::abs(getScreenHeight()) * ar_i, std::abs(getScreenHeight())};
            float middle_point = (_screen_boundaries.x_min + _screen_boundaries.x_max) / 2;

            // boundaries
            if (_screen_boundaries.x_min < _screen_boundaries.x_max) {
                _sub_screen_boundaries.x_min = middle_point - new_sub_screen_resolution.x / 2;
                _sub_screen_boundaries.x_max = middle_point + new_sub_screen_resolution.x / 2;
            } else {
                _sub_screen_boundaries.x_min = middle_point + new_sub_screen_resolution.x / 2;
                _sub_screen_boundaries.x_max = middle_point - new_sub_screen_resolution.x / 2;
            }

            // sidebar
            _sidebar_size = {(getScreenWidth() - new_sub_screen_resolution.x) / 2, getScreenHeight()};
            _sidebar_1_position = {_sidebar_size.x / 2, getScreenHeight() / 2};
            _sidebar_2_position = {getScreenWidth() - _sidebar_size.x / 2, getScreenHeight() / 2};
        } else {
            new_sub_screen_resolution = {getScreenWidth(), getScreenWidth() / ar_i};
            float middle_point = (_screen_boundaries.y_min + _screen_boundaries.y_max) / 2;

            // boundaries
            if (_screen_boundaries.y_min < _screen_boundaries.y_max) {
                _sub_screen_boundaries.y_min = middle_point - new_sub_screen_resolution.y / 2;
                _sub_screen_boundaries.y_max = middle_point + new_sub_screen_resolution.y / 2;
            } else {
                _sub_screen_boundaries.y_min = middle_point + new_sub_screen_resolution.y / 2;
                _sub_screen_boundaries.y_max = middle_point - new_sub_screen_resolution.y / 2;
            }

            // sidebar
            _sidebar_size = {getScreenWidth(), (getScreenHeight() - new_sub_screen_resolution.y) / 2};
            _sidebar_1_position = {getScreenWidth() / 2, _sidebar_size.y / 2};
            _sidebar_2_position = {getScreenWidth() / 2, getScreenHeight() - _sidebar_size.y / 2};
        }

        _sidebar_size = projectSizeSubScreenToWorld(_sidebar_size);
        _sidebar_1_position = projectCoordSubScreenToWorld(_sidebar_1_position);
        _sidebar_2_position = projectCoordSubScreenToWorld(_sidebar_2_position);
    }

    Vector2f Camera::projectCoordWorldToSubScreen(const Vector2f &coord, bool ui_space) const {
        float alpha_x;
        float alpha_y;

        if (ui_space) {
            alpha_x = (coord.x - _boundaries.x_min) / getWidth();
            alpha_y = (coord.y - _boundaries.y_min) / getHeight();
        } else {
            Vector2f new_coord = coord - getPosition();
            alpha_x = (new_coord.x - _boundaries.x_min) / getWidth();
            alpha_y = (new_coord.y - _boundaries.y_min) / getHeight();
        }

        return {lerp(_sub_screen_boundaries.x_min, _sub_screen_boundaries.x_max, alpha_x),
                lerp(_sub_screen_boundaries.y_min, _sub_screen_boundaries.y_max, alpha_y)};
    }

    float Camera::projectVerticalSizeWorldToSubScreen(float vertical_size) const {
        return (getSubScreenHeight() / getHeight()) * vertical_size;
    }

    float Camera::projectHorizontalSizeWorldToSubScreen(float horizontal_size) const {
        return (getSubScreenWidth() / getWidth()) * horizontal_size;
    }

    Vector2f Camera::projectSizeWorldToSubScreen(const Vector2f &size) const {
        return {(getSubScreenWidth() / getWidth()) * size.x,
                (getSubScreenHeight() / getHeight()) * size.y};
    }

    Vector2f Camera::projectCoordScreenToWorld(const Vector2f &coord) const {
        float alpha_x = (coord.x - _screen_boundaries.x_min) /
                        (_screen_boundaries.x_max - _screen_boundaries.x_min);
        float alpha_y = (coord.y - _screen_boundaries.y_min) /
                        (_screen_boundaries.y_max - _screen_boundaries.y_min);

        return {lerp(_boundaries.x_min, _boundaries.x_max, alpha_x),
                lerp(_boundaries.y_min, _boundaries.y_max, alpha_y)};
    }

    Vector2f Camera::projectSizeScreenToWorld(const Vector2f &size) const {
        return {(getWidth() / getScreenWidth()) * size.x,
                (getHeight() / getScreenHeight()) * size.y};
    }

    Vector2f Camera::projectCoordSubScreenToWorld(const Vector2f &coord) const {
        float alpha_x = (coord.x - _sub_screen_boundaries.x_min) /
                        (_sub_screen_boundaries.x_max - _sub_screen_boundaries.x_min);
        float alpha_y = (coord.y - _sub_screen_boundaries.y_min) /
                        (_sub_screen_boundaries.y_max - _sub_screen_boundaries.y_min);

        return {lerp(_boundaries.x_min, _boundaries.x_max, alpha_x),
                lerp(_boundaries.y_min, _boundaries.y_max, alpha_y)};
    }

    Vector2f Camera::projectSizeSubScreenToWorld(const Vector2f &size) const {
        return {(getWidth() / getSubScreenWidth()) * size.x,
                (getHeight() / getSubScreenHeight()) * size.y};
    }
} // engine