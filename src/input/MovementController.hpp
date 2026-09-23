#pragma once
#include <bitset>
#include <memory>

namespace input {
    enum class KeyStatus {
        Pressed,
        Released,
    };

    class AController {
        friend class InputHandler;
    private:
        std::bitset<64> _status;
    protected:
        const bool _get(int index) const noexcept;
    };
    
    class MovementController : public AController {
    public:

        const bool up()     const noexcept;
        const bool down()   const noexcept;
        const bool left()   const noexcept;
        const bool right()  const noexcept;

    };

    class InputHandler {
    private:
        std::unique_ptr<MovementController> _movement_controller;
    public:
        void update_movement_controller();
    };
}