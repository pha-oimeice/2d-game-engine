#pragma once
#include "RigidBody.hpp"
#include "dsa/SparseSet.hpp"
#include <cmath>

namespace physics {

    class PhysicsWorld {
    private:
        int _tick;
        dsa::SparseSet<RigidBodyKinematic> storage;
    };

    // x, y is the center
    // w, h is half of its width and height
    struct AABB {
        float x;
        float y;
        float w;
        float h;
    };
    
}
