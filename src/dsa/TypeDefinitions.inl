namespace td {
    namespace internal {
        template <typename T>
        NonZero<T> NonZero<T>::operator + (const NonZero<T>& rhs) const {
            return NonZero<T>(value + rhs.value);
        }

        template <typename T>
        NonZero<T> NonZero<T>::operator - (const NonZero<T>& rhs) const {
            return NonZero<T>(value - rhs.value);
        }

        template <typename T>
        NonZero<T> NonZero<T>::operator * (const NonZero<T>& rhs) const {
            return NonZero<T>(value * rhs.value);
        }

        template <typename T>
        NonZero<T> NonZero<T>::operator / (const NonZero<T>& rhs) const {
            return NonZero<T>(value / rhs.value);
        }

        template <typename T>
        NonZero<T>& NonZero<T>::operator += (const NonZero<T>& rhs) {
            value += rhs.value;
            return *this;
        }

        template <typename T>
        NonZero<T>& NonZero<T>::operator -= (const NonZero<T>& rhs) {
            value -= rhs.value;
            return *this;
        }

        template <typename T>
        NonZero<T>& NonZero<T>::operator *= (const NonZero<T>& rhs) {
            value *= rhs.value;
            return *this;
        }

        template <typename T>
        NonZero<T>& NonZero<T>::operator /= (const NonZero<T>& rhs) {
            value /= rhs.value;
            return *this;
        }

        template <typename T>
        NonZero<T> NonZero<T>::operator + () const {
            return NonZero<T>(+value);
        }

        template <typename T>
        NonZero<T> NonZero<T>::operator - () const {
            return NonZero<T>(-value);
        }

        template <typename T>
        NonZero<T>& NonZero<T>::operator ++ () {
            ++value;
            return *this;
        }

        template <typename T>
        NonZero<T> NonZero<T>::operator ++ (int) {
            NonZero<T> previous(*this);
            ++(*this);
            return previous;
        }

        template <typename T>
        NonZero<T>& NonZero<T>::operator -- () {
            --value;
            return *this;
        }

        template <typename T>
        NonZero<T> NonZero<T>::operator -- (int) {
            NonZero<T> previous(*this);
            --(*this);
            return previous;
        }

        template <typename T>
        bool NonZero<T>::operator == (const NonZero<T>& rhs) const {
            return value == rhs.value;
        }

        template <typename T>
        bool NonZero<T>::operator != (const NonZero<T>& rhs) const {
            return value != rhs.value;
        }

        template <typename T>
        bool NonZero<T>::operator < (const NonZero<T>& rhs) const {
            return value < rhs.value;
        }

        template <typename T>
        bool NonZero<T>::operator <= (const NonZero<T>& rhs) const {
            return value <= rhs.value;
        }

        template <typename T>
        bool NonZero<T>::operator > (const NonZero<T>& rhs) const {
            return value > rhs.value;
        }

        template <typename T>
        bool NonZero<T>::operator >= (const NonZero<T>& rhs) const {
            return value >= rhs.value;
        }
    }
}
