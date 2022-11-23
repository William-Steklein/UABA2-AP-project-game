#ifndef GAME_ENGINE_CAMERA_H
#define GAME_ENGINE_CAMERA_H


#include "engine/math/math_utils.h"
#include "engine/math/Vector2f.h"
#include "engine/camera/ViewBoundaries.h"

namespace engine {

    class Camera {
    public:
        Camera();

        Camera(float left, float right, float bottom, float top);

        ~Camera() = default;

        const Vector2f &getPosition() const;

        void setPosition(const Vector2f &position);

        float getWidth() const;

        float getHeight() const;

        float getScreenWidth() const;

        float getScreenHeight() const;

        float getSubscreenWidth() const;

        float getSubscreenHeight() const;

        Vector2f projectCoordWorldToSubScreen(const Vector2f &coord) const;

        Vector2f projectSizeWorldToSubScreen(const Vector2f &size) const;

    private:
        Vector2f _position;

        ViewBoundaries _boundaries;
        ViewBoundaries _screen_boundaries;
        Vector2f _sub_screen_aspect_ratio;
        ViewBoundaries _sub_screen_boundaries;
    };

} // engine

#endif //GAME_ENGINE_CAMERA_H
