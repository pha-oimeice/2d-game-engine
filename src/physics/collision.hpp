#pragma once
#include "TypeDefinitions.hpp"
#include "dsa/Vector2.hpp"
#include "ecs/ECS.hpp"
#include <vector>

namespace physics {
    enum RigidBodyEnum {
        Static = 0,
        Kinematic = 1,
        Dynamic = 2,
    };
    struct RigidBody final : ecs::AComponent {
    public:
        explicit inline RigidBody(td::Id id=0, RigidBodyEnum data=RigidBodyEnum::Static) : id(id), data(data) {}
        td::Id id;
        RigidBodyEnum data;
    };

    struct Collider final : ecs::AComponent {
    public:
        explicit inline Collider(float radius=1.0f) : radius(radius) {}
        float radius;
    };

    struct Velocity final : ecs::AComponent {
    public:
        explicit inline Velocity(dsa::Vector2f data=dsa::Vector2f(.0f, .0f)) : data(data) {}
        dsa::Vector2f data;
    };

}
