#pragma once
#include "AComponent.hpp"
#include "my_window/InputHandler.hpp"

namespace com {
    // Component
    // Read-only access to controller status,
    // where the modification is only allow to owner of the controller.
    struct ControllerView final : ecs::AComponent {
    public:
        explicit inline ControllerView() {}
        const window::AController* controller_ref;
    };
}