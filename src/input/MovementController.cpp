#include "MovementController.hpp"

namespace input {
    const bool AController::_get(int index) const noexcept {
        if (0 <= index && index <= 63) {
            return this->_status[index];
        }
        return false;
    }
}