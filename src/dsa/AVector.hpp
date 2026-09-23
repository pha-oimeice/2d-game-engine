#pragma once

namespace dsa {
    template <typename T, size_t N>
    struct AVector {
    public:
        explicit inline AVector() {}
        static constexpr size_t DIMENSION = N;
        T _data[N];

        bool operator == (const AVector<T, N> & rhs) const noexcept;
        bool operator != (const AVector<T, N> & rhs) const noexcept;

        AVector<T, N> operator + (const AVector<T, N> & rhs) const noexcept;
        AVector<T, N> operator - (const AVector<T, N> & rhs) const noexcept;
        AVector<T, N> operator * (const T rhs) const noexcept;
        AVector<T, N> operator / (const T rhs) const;

        void operator += (const AVector<T, N> & rhs) noexcept;
        void operator -= (const AVector<T, N> & rhs) noexcept;
        void operator *= (const T rhs) noexcept;
        void operator /= (const T rhs);
    };
}

#include "AVector.inl"