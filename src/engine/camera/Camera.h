#ifndef GAME_ENGINE_CAMERA_H
#define GAME_ENGINE_CAMERA_H


#include <tuple>

#include "engine/math/math_utils.h"
#include "engine/math/Vector2f.h"
#include "engine/camera/ViewBoundaries.h"
#include "engine/logging/Logger.h"

namespace engine {

    class Camera {
    public:
        Camera();

        Camera(float left, float right, float bottom, float top);

        ~Camera() = default;

        const Vector2f &getPosition() const;

        void setPosition(const Vector2f &position);

        void setScreenBoundaries(float left, float right, float bottom, float top);

        float getWidth() const;

        float getHeight() const;

        float getScreenWidth() const;

        float getScreenHeight() const;

        float getSubScreenWidth() const;

        float getSubScreenHeight() const;

        std::tuple<Vector2f, Vector2f, Vector2f> getSidebarData() const;

        void updateSubScreenResolution();

        Vector2f projectCoordWorldToSubScreen(const Vector2f &coord) const;

        float projectVerticalSizeWorldToSubScreen(float vertical_size) const;

        float projectHorizontalSizeWorldToSubScreen(float horizontal_size) const;

        Vector2f projectSizeWorldToSubScreen(const Vector2f &size) const;

        Vector2f projectCoordScreenToWorld(const Vector2f &coord) const;

        Vector2f projectSizeScreenToWorld(const Vector2f &size) const;

        Vector2f projectCoordSubScreenToWorld(const Vector2f &coord) const;

        Vector2f projectSizeSubScreenToWorld(const Vector2f &size) const;

    private:
        Vector2f _position;

        ViewBoundaries _boundaries;
        ViewBoundaries _screen_boundaries;

        Vector2f _sub_screen_aspect_ratio;
        ViewBoundaries _sub_screen_boundaries;

        Vector2f _sidebar_size;
        Vector2f _sidebar_1_position;
        Vector2f _sidebar_2_position;
    };

} // engine

#endif //GAME_ENGINE_CAMERA_H
