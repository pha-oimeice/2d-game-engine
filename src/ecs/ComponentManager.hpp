#pragma once
#include "ECSDefinition.hpp"
#include "dsa/IdGenerator.hpp"
#include "dsa/SparseSet.hpp"
#include <memory>
#include <unordered_map>

namespace ecs {

    class IComponentStorage { };

    template <RawComponent T_Component>
    class ComponentStorage final : public IComponentStorage {
        friend class ComponentManager;
    private:
        dsa::SparseSet<T_Component> _storage;
    public:
    };

    class ComponentManager final {
    private:

        std::unordered_map<ComponentId, std::unique_ptr<IComponentStorage>> _storages;

        template <RawComponent T_Component>
        void _insert_one(EntityId e, T_Component component);

        template <RawComponent T_Component>
        void _add_component();

    public:

        explicit inline ComponentManager() {}

        virtual ~ComponentManager() = default;

        template <RawComponent... T_Components>
        inline void add_components();

        template <RawComponent T_Component>
        dsa::SparseSet<T_Component>& get_component_storage();

        template <QueryComponent T_Component>
        T_Component& get_component(EntityId e);

        template <RawComponent... T_Components>
        void insert(EntityId e, T_Components... components);

        template <RawComponent... T_Components>
        void remove(EntityId e);

        template <RawComponent T_Component>
        std::vector<EntityId> find_entities_for_component();

        template <RawComponent... T_Components>
        std::vector<EntityId> find_archetypes();
    };
}

#include "ComponentManager.inl"