#include "PhysicWorld.hpp"
#include "dsa/SparseSet.hpp"
#include <memory>
#include <vector>

// class definition
namespace physics {
    struct PhysicWorld::Internal {
        std::size_t tick;

        dsa::SparseSet<RigidBody> rbs;

        dsa::SparseSet<AABB> colliders;

        dsa::SparseSet<PhysicDescriptor> descs;

        std::vector<AABBOverlapEvent> aabb_overlap_event_cache;
    };
}

// function declaration
namespace physics {
    template <typename T>
    void clamp(T& n, T min, T max);

    Vector2f aabb_overlap_area(const AABB& a, const AABB& b);

    void apply_fluid_drag(PhysicDescriptor& desc);

    void apply_friction(PhysicDescriptor& desc);

    void apply_resultant_force(PhysicDescriptor& desc);

    void apply_mechanic_integrations(PhysicDescriptor& desc);
}

// class method definitions
namespace physics {

    PhysicWorld::PhysicWorld() {
        this->_internal = std::make_unique<Internal>();
    }

    RigidBodyId PhysicWorld::add_rigid_body(const RigidBody rb) {
        auto& class_data = *this->_internal.get();

        switch (rb) {
            case RigidBody::Static:
                break;
            case RigidBody::Kinematic:
                break;
            default:
                break;
        }

        return 0;
    }

    void PhysicWorld::remove_rigid_body(RigidBodyId id) noexcept {
        auto& class_data = *this->_internal.get();

    }

    void PhysicWorld::update() {
        auto& class_data = *this->_internal.get();

        // 1. update the physic descriptors
        for (auto& dense_data : class_data.descs.get_dense_storage()) {
            auto& desc = dense_data.data;

            apply_fluid_drag(desc);
            
            apply_resultant_force(desc);
            
            apply_mechanic_integrations(desc);
        }

        // 2. find all aabb overlap events
        for (const auto& aabb_0 : class_data.colliders.get_dense_storage()) {
            for (const auto& aabb_1 : class_data.colliders.get_dense_storage()) {
                // same address => same aabb => skip
                if (&aabb_0 == &aabb_1) {
                    continue;
                }
                // check all aabb, forward events
                auto overlap = aabb_overlap_area(aabb_0.data, aabb_1.data);
                // X Overlap
                if (overlap.x > 0.f) {

                }
                // Y Overlap
                if (overlap.y > 0.f) {
                    
                }
            }
        }

        // 3. classify events

        // 4. solve (fix the full overlaps) and finalize positions of all kinematic rigidbodys
    }

}

// function definition
namespace physics {

    template <typename T>
    void clamp(T& n, T min, T max) {
        n = std::min(max, n);
        n = std::max(min, n);
    }
    
    Vector2f aabb_overlap_area(const AABB& a, const AABB& b) {
        Vector2f overlap;
        auto& w = overlap.x;
        auto& h = overlap.y;
        w = a.wh_half.x + b.wh_half.y - std::abs(a.center.x-b.center.x);
        h = a.wh_half.y + b.wh_half.y - abs(a.center.y-b.center.y);
        clamp(w, 0.f, 1e18f);
        clamp(h, 0.f, 1e18f);
        return overlap;
    }

    void apply_fluid_drag(PhysicDescriptor& desc) {
        auto&& velocity_square = Vector2f(
            desc.velocity.x * desc.velocity.x,
            desc.velocity.y * desc.velocity.y
        );

        desc.force += velocity_square
                * desc.drag_coefficient
                * desc.crossectional_area
                * desc.environment_fluid_viscosity;
    }

    void apply_friction(PhysicDescriptor& desc) {
        // WIP
    }

    void apply_resultant_force(PhysicDescriptor& desc) {
        desc.acceleration += desc.force * desc.mass_inv;
    }

    void apply_mechanic_integrations(PhysicDescriptor& desc) {
        desc.velocity += desc.acceleration;
        desc.position += desc.velocity;
    }

}
