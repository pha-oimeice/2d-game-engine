#include "graphics.hpp"
#include "ecs/ECS.hpp"
#include "my_window/Graphics.hpp"
#include "my_window/Window.hpp"

namespace sys {
    void update_shape_transform() {
        auto query = ecs::get_manager().read<
            ecs::Transform,
            window::MyShape
        >();
        return;
        for (auto& [transform, shape] : query) {
            window::get_window().update_drawable(shape.get_id(), transform);
        }
    }
}