#pragma once
#include "ECSDefinition.hpp"
#include "AComponent.hpp"
#include "dsa/IdGenerator.hpp"
#include <memory>
#include <unordered_set>
#include <unordered_map>

namespace ecs {

    template <typename T_Component>
    requires (std::derived_from<T_Component, AComponent>)
    class ComponentStorage final : AComponent {
        friend class ComponentManager;
    private:

        dsa::SparseSet<T_Component> _storage;

    public:

    };

    class ComponentManager final {
    private:

        std::unordered_set<ComponentId> _component_registry;

        std::unordered_map<ComponentId, std::unique_ptr<AComponent>> _storages;

    public:

        explicit inline ComponentManager() {}

        virtual ~ComponentManager() = default;

        template <typename T_Component>
        requires (std::derived_from<T_Component, AComponent>)
        void add_component();

        template <typename... T_Components>
        inline void add_components();

        template <typename T_Component>
        requires (std::derived_from<T_Component, AComponent>)
        ComponentStorage<T_Component>& get_component_storage();

        template <typename T_Component>
        requires (std::derived_from<T_Component, AComponent>)
        T_Component& get_component(EntityId e);

        template <typename... T_Components>
        void insert(EntityId e, T_Components... components);

        template <typename... T_Components>
        void remove(EntityId e);

        template <typename T_Component>
        requires (std::derived_from<T_Component, AComponent>)
        std::unique_ptr<std::vector<EntityId>> find_entities_for_component();

        template <typename... T_Components>
        std::unique_ptr<std::vector<EntityId>> find_archetypes();
    };
}

#include "ComponentManager.inl"