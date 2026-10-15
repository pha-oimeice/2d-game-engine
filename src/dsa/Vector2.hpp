#pragma once
#include <array>

namespace dsa {
    
    template <typename T>
    struct Vector2 {
        T x;
        T y;
        inline Vector2(
            T x = T(),
            T y = T()
        ) : x(x), y(y) {}

        Vector2<T> operator + (const Vector2<T> & rhs) const;
        Vector2<T> operator - (const Vector2<T> & rhs) const;
        Vector2<T> operator * (const T& rhs) const;
        Vector2<T> operator / (const T& rhs) const;

        void operator += (const Vector2<T> & rhs);
        void operator -= (const Vector2<T> & rhs);
        void operator *= (const T& rhs);
        void operator /= (const T& rhs);
    };

    using Vector2f = Vector2<float>;

    struct Transform2 {
        explicit inline Transform2(
            Vector2f translation = Vector2f(0.f, 0.f),
            float rotation = 0.f,
            Vector2f scale = Vector2f(1.f, 1.f)
        ) : translation(translation),
            rotation(rotation),
            scale(scale) { }

        Vector2f translation;
        float rotation;
        Vector2f scale;
    };
}

#include "Vector2.inl"