

namespace dsa {
    template <typename T>
    Vector2<T> Vector2<T>::operator + (const Vector2<T>& rhs) const {
        return Vector2<T>(x + rhs.x, y + rhs.y);
    }

    template <typename T>
    Vector2<T> Vector2<T>::operator - (const Vector2<T>& rhs) const {
        return Vector2<T>(x - rhs.x, y - rhs.y);
    }

    template <typename T>
    Vector2<T> Vector2<T>::operator * (const T& rhs) const {
        return Vector2<T>(x * rhs, y * rhs);
    }

    template <typename T>
    Vector2<T> Vector2<T>::operator / (const T& rhs) const {
        return Vector2<T>(x / rhs, y / rhs);
    }

    template <typename T>
    void Vector2<T>::operator += (const Vector2<T>& rhs) {
        *this = *this + rhs;
    }

    template <typename T>
    void Vector2<T>::operator -= (const Vector2<T>& rhs) {
        *this = *this - rhs;
    }

    template <typename T>
    void Vector2<T>::operator *= (const T& rhs) {
        *this = *this * rhs;
    }

    template <typename T>
    void Vector2<T>::operator /= (const T& rhs) {
        *this = *this / rhs;
    }
}
