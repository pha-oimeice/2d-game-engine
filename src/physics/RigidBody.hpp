#pragma once
#include "dsa/Vector2.hpp"

namespace physics {

    struct RigidBodyStatic {
        explicit inline RigidBodyStatic() {}
        dsa::Vector2f translation;
        float rotation;
    };

    struct RigidBodyKinematic : public RigidBodyStatic {
        explicit inline RigidBodyKinematic() {}
        dsa::Vector2f velocity;
        dsa::Vector2f acceleration;
        dsa::Vector2f force;
        float angular_velocity;
    };

    struct RigidBodyDynamic : public RigidBodyKinematic {
        explicit inline RigidBodyDynamic() {}
    };

}