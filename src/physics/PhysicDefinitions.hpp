#pragma once
#include "SFML/System/Vector2.hpp"
#include <memory>
#include <vector>

namespace physics {

    // replace this with VectorPP later
    using Vector2f = sf::Vector2f;
    using Scalar = float;

    using RigidBodyId = int;

    enum class RigidBody {
        Static = 0,
        Kinematic = 1,
        Dynamic = 2,
    };

    /// @brief Multiple mutex states for kinematic rigidbody
    enum RigidBodyKinematicState {
        // no system
        InSpace = 0,
        // buoyancy system (including air), gravity, fluid friction
        Submerged = 1,
        // ground friction, relative stationary with ground (ground may be kinematic)
        Grounded = 2,
    };

    struct AABB final {
        Vector2f center;
        Vector2f wh_half;
    };

    struct AABBOverlapEvent final {
        Vector2f previous_overlap;
        Vector2f current_overlap;
    };

    /// @brief channels indicate filters
    struct CollisionTag final {
        std::vector<int> channel;
        bool whiltlist = true;
    };

    /// @brief The descriptor of center of mass
    /// @brief
    /// @brief - Vector2f is a vector
    /// @brief - float is a scalar
    struct PhysicDescriptor final {
        Vector2f position;
        Vector2f velocity;
        Vector2f acceleration;
        Vector2f force;

        Scalar mass;
        Scalar mass_inv;
        Scalar crossectional_area;
        Scalar crossectional_area_inv;
        Scalar volume;
        Scalar volume_inv;

        Scalar friction_coefficient;
        Scalar drag_coefficient;
        Scalar environment_fluid_viscosity;
    };

}