#pragma once
#include "PhysicDefinitions.hpp"


namespace physics {

    class PhysicWorld {
    public:

        explicit PhysicWorld();

        /// @brief Add a new rigidbody, automatically create corresponding collider and descriptor. (if necessary)
        /// @param rb Note that once added, the rigidbody type is immutable
        /// @return 
        RigidBodyId add_rigid_body(const RigidBody rb);

        /// @brief Remove a existing rigidbody
        /// @param id rigidbody id
        void remove_rigid_body(RigidBodyId id) noexcept;

        /// @brief - This method should only be used for Kinematic rigidbody.
        /// @brief
        /// @brief - Modify dynamic rigidbody's descriptor may cause strange behavior.
        /// @param rb_id rigidbody id
        /// @return pointer, nullptr if does not exists or inaccessible
        PhysicDescriptor* get_desc(RigidBodyId rb_id) noexcept;

        /// @brief Allow read access to all physic descriptor
        /// @param rb_id rigidbody id
        /// @return pointer, nullptr if does not exists
        const PhysicDescriptor* get_desc(RigidBodyId rb_id) const noexcept;

        AABB* get_aabb(RigidBodyId rb_id) noexcept;

        const AABB* get_aabb(RigidBodyId rb_id) const noexcept;

        /// @brief atomically update the world, increment this->_tick by 1.
        void update();

        /// @brief 
        /// @return current tick
        std::size_t get_tick() const noexcept;

    private:
    
        struct Internal;
        std::unique_ptr<Internal> _internal;

    };
}