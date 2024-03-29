#ifndef GAME_ENGINE_MATH_UTILS_H
#define GAME_ENGINE_MATH_UTILS_H


#include <cmath>
#include "engine/math/Vector2f.h"

namespace engine {

    // float linear interpolation
    float lerp(float x0, float x1, float alpha);

    // vector linear interpolation
    Vector2f lerp(const Vector2f &p0, const Vector2f &p1, float alpha);

    float toRadian(float angle);

    float toDegree(float angle);

    void degreeMod(float &angle);

    void radianMod(float &angle);

    /**
     * Source: "https://stackoverflow.com/a/565282/12557703"
     */
    bool linesegmentIntersection(const Vector2f &l1p1, const Vector2f &l1p2, const Vector2f &l2p1,
                                 const Vector2f &l2p2, Vector2f &intersection1,
                                 Vector2f &intersection2, bool &is_collinear);

    float sigmoid(float x, float a, float b);

    float clamp(float value, float min, float max);

    Vector2f clamp(const Vector2f &value, const Vector2f &min, const Vector2f &max);

} // engine

#endif //GAME_ENGINE_MATH_UTILS_H
