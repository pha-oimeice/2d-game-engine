#pragma once

namespace dsa {
    template <typename T>
    struct Vector2 {
        explicit inline Vector2(T x=.0f, T y=.0f) : x(x), y(y) {}
        T x;
        T y;
    };
    using Vector2f = Vector2<float>;
}