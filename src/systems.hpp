#pragma once

namespace sys {
    
    void test_system();

    void overlap_detection();
    
    // Synchronize logic transform and render transform
    void update_transform();

    void update_shape();

    void shape_bounce_on_edge();

    void create_enemies();
}