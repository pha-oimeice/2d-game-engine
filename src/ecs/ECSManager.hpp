#pragma once
#include <memory>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <concepts>
#include "dsa/IdGenerator.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"
#include "ResourceManager.hpp"

namespace ecs {

    // runtime ecs manager
    // purpose 0: synchronize read/write lock per tick to avoid conflict.
    // purpose 1: update FSM, add_system is not allowed after explicit run().
    class ECSManager final {

    private:

        ComponentManager _component_manager;

        SystemManager _system_manager;

        ResourceManager _resource_manager;

        dsa::IdGenerator _entity_id_generator;

    public:

        explicit inline ECSManager() {}

        virtual ~ECSManager() = default;

        template <QueryComponent... T_Components>
        std::vector<std::tuple<T_Components&...> > read();

        template <RawComponent... T_Components>
        EntityId create_entity(T_Components... components);

        void remove_entity(EntityId e);

        void init();

        void run();

        void stop();

        template <QueryResource T_Resource>
        T_Resource& get_resource();

        void add_system(
            const SystemFn system,
            const SystemDescriptor system_desc = SystemDescriptor()
        );

    };

    inline ECSManager& get_manager() {
        static ECSManager ECS_MANAGER;
        return ECS_MANAGER;
    }
}

#include "ECSManager.inl"