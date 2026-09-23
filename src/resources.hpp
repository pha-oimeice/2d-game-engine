#pragma once
#include "ecs/Abstract.hpp"
#include "components.hpp"

namespace resources {

    struct Player : ecs::AResource {
        components::Transform transform;
        int health_points;
        
    };
}

