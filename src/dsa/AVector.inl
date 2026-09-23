

namespace dsa {
    template <typename T, size_t N>
    bool AVector<T, N>::operator == (const AVector<T, N> & rhs) const noexcept {
        for (size_t i = 0; i < N; i++) {
            if (this->_data[i] != rhs[i]) {
                return false;
            }
        }
        return true;
    }
    template <typename T, size_t N>
    bool AVector<T, N>::operator != (const AVector<T, N> & rhs) const noexcept {
        return !(*this == rhs);
    }

    template <typename T, size_t N>
    AVector<T, N> AVector<T, N>::operator + (const AVector<T, N> & rhs) const noexcept {
        AVector<T, N> result;
        for (size_t i = 0; i < N; i++) {
            result._data[i] = this->_data[i] + rhs._data[i];
        }
        return result;
    }
    template <typename T, size_t N>
    AVector<T, N> AVector<T, N>::operator - (const AVector<T, N> & rhs) const noexcept {
        AVector<T, N> result;
        for (size_t i = 0; i < N; i++) {
            result._data[i] = this->_data[i] - rhs._data[i];
        }
        return result;
    }
    template <typename T, size_t N>
    AVector<T, N> AVector<T, N>::operator * (const T rhs) const noexcept {
        AVector<T, N> result;
        for (size_t i = 0; i < N; i++) {
            result._data[i] = this->_data[i] * rhs;
        }
    }
    template <typename T, size_t N>
    AVector<T, N> AVector<T, N>::operator / (const T rhs) const {
    }

    template <typename T, size_t N>
    void AVector<T, N>::operator += (const AVector<T, N> & rhs) noexcept {

    }
    template <typename T, size_t N>
    void AVector<T, N>::operator -= (const AVector<T, N> & rhs) noexcept {

    }
    template <typename T, size_t N>
    void AVector<T, N>::operator *= (const T rhs) noexcept {

    }
    template <typename T, size_t N>
    void AVector<T, N>::operator /= (const T rhs) {
        
    }
}