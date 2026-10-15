#pragma once

namespace td {
    
    namespace internal {
        template <typename T>
        struct NonZero {
            explicit inline NonZero(T value = 0) : value(value) {}
            T value;
            // use is_valid() to check if value equals 0
            inline constexpr bool is_valid() const noexcept {
                return value != 0;
            }

            
            NonZero<T> operator + (const NonZero<T>& rhs) const;
            NonZero<T> operator - (const NonZero<T>& rhs) const;
            NonZero<T> operator * (const NonZero<T>& rhs) const;
            NonZero<T> operator / (const NonZero<T>& rhs) const;

            NonZero<T>& operator += (const NonZero<T>& rhs);
            NonZero<T>& operator -= (const NonZero<T>& rhs);
            NonZero<T>& operator *= (const NonZero<T>& rhs);
            NonZero<T>& operator /= (const NonZero<T>& rhs);

            NonZero<T> operator + () const;
            NonZero<T> operator - () const;
            NonZero<T>& operator ++ ();
            NonZero<T> operator ++ (int);
            NonZero<T>& operator -- ();
            NonZero<T> operator -- (int);

            bool operator == (const NonZero<T>& rhs) const;
            bool operator != (const NonZero<T>& rhs) const;
            bool operator < (const NonZero<T>& rhs) const;
            bool operator <= (const NonZero<T>& rhs) const;
            bool operator > (const NonZero<T>& rhs) const;
            bool operator >= (const NonZero<T>& rhs) const;
        };
    }

    using PositiveId = internal::NonZero<unsigned long long>;

    using Id = int;
}

#include "TypeDefinitions.inl"