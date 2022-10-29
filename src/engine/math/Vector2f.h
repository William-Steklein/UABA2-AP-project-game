#ifndef GAME_ENGINE_VECTOR2F_H
#define GAME_ENGINE_VECTOR2F_H


#include <cmath>
#include <iostream>

namespace engine {

    class Vector2f {
    public:
        float x;
        float y;

        Vector2f();

        Vector2f(float _x, float _y);

        Vector2f(const Vector2f &other);

        Vector2f &operator=(const Vector2f &other);

        Vector2f operator+(const Vector2f &other) const;

        Vector2f operator+(float scalar) const;

        friend Vector2f operator+(float scalar, const Vector2f &other);

        Vector2f &operator+=(const Vector2f &other);

        Vector2f &operator+=(float scalar);

        Vector2f operator-(const Vector2f &other) const;

        Vector2f operator-(float scalar) const;

        friend Vector2f operator-(float scalar, const Vector2f &other);

        Vector2f &operator-=(const Vector2f &other);

        Vector2f &operator-=(float scalar);

        Vector2f operator*(float scalar) const;

        friend Vector2f operator*(float scalar, const Vector2f &other);

        Vector2f &operator*=(float scalar);

        Vector2f operator/(float scalar) const;

        friend Vector2f operator/(float scalar, const Vector2f &other);

        Vector2f &operator/=(float scalar);

        bool operator==(const Vector2f &other) const;

        bool operator<(const Vector2f &other) const;

        bool operator<=(const Vector2f &other) const;

        bool operator>(const Vector2f &other) const;

        bool operator>=(const Vector2f &other) const;

        bool empty() const;

        void clear();

        float length() const;

        void normalize();

        Vector2f normalized();

        float dotProduct(const Vector2f &other) const;

        float crossProduct(const Vector2f &other) const;

        void rotate(float angle_radian, const Vector2f &pivot_point = {0, 0});

        Vector2f rotated(float angle_radian, const Vector2f &pivot_point = {0, 0}) const;

        void scale(const Vector2f &scale, const Vector2f &pivot_point = {0, 0});

        Vector2f scaled(const Vector2f &scale, const Vector2f &pivot_point = {0, 0}) const;

        friend std::ostream &operator<<(std::ostream &os, const Vector2f &vector);

        std::string toString() const;
    };

} // engine

#endif //GAME_ENGINE_VECTOR2F_H
