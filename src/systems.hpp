#pragma once
#include "components.hpp"
#include "ecs/ECS.hpp"

namespace sys {
    
    void test_system();

    void test_system_1(
        ecs::Query<components::Transform> query
    );

    void overlap_detection();
    
    // Synchronize logic transform and render transform
    void update_transform();

    void update_shape();

    void shape_bounce_on_edge();

    void create_enemies();
}