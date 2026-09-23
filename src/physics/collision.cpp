#include "collision.hpp"
#include "ecs/ECS.hpp"
#include <vector>
#include <cmath>

namespace physics {

    float aabb_overlap_area(
        const AABB& a,
        const AABB& b
    ) {
        float dx = a.w+b.w - abs(a.x-b.x);
        float dy = a.h+b.h - abs(a.y-b.y);
        if (dx > 0.f && dy > 0.f) {
            return 0.f;
        }
        
        return 0.f;
    }
    
    void resolve_overlap_area(
        const AABB& a,
        const AABB& b,
        AABB c
    ) {

    }

    void resolve_normals(

    ) {

    }

}
