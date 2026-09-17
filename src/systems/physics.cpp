#include "physics.hpp"
#include "ecs/ECS.hpp"
#include "physics/collision.hpp"

namespace sys {
    void overlap_detection() {
        auto query = ecs::get_manager().read<
            physics::RigidBody,
            physics::Collider,
            ecs::Transform,
            physics::Velocity
        >();
        for (auto [rigid_body_a, collider_a, transform_a, velocity_a] : query) {
            for (auto [rigid_body_b, collider_b, transform_b, velocity_b] : query) {
                if (rigid_body_a.id != rigid_body_b.id && (
                    pow(static_cast<double>(transform_a.translation.x-transform_b.translation.x), 2.0) +
                    pow(static_cast<double>(transform_a.translation.y-transform_b.translation.y), 2.0) <
                    pow(static_cast<double>(collider_a.radius+collider_b.radius), 2.0))
                ) {
                    velocity_a.data.x *= -1.0f;
                    velocity_a.data.y *= -1.0f;
                    velocity_b.data.x *= -1.0f;
                    velocity_b.data.y *= -1.0f;
                }
            }
        }
    }
}