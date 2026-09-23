#include <iostream>

namespace ecs {

    template <RawComponent... T_Components>
    inline void ComponentManager::add_components() {
        (this->_add_component<T_Components>(), ...);
    }

    template <QueryComponent T_Component>
    T_Component& ComponentManager::get_component(EntityId e) {

        using T_RawComponent = std::remove_cvref_t<T_Component>;

        if constexpr (std::is_const_v<std::remove_reference_t<T_Component>>) {
            // find sparse set
            const auto& sparse_set = this->get_component_storage<T_RawComponent>();

            // try to find component for entity e.
            const auto* dense_data = sparse_set.get_ref(e);
            
            if (dense_data == nullptr) {
                throw "Trying to get component that does not exists.";
            }
            return dense_data->data;
        }
        else {
            // find sparse set
            auto& sparse_set = this->get_component_storage<T_RawComponent>();

            // try to find component for entity e.
            auto* dense_data = sparse_set.get_ref(e);
            
            if (dense_data == nullptr) {
                throw "Trying to get component that does not exists.";
            }
            return dense_data->data;
        }
        
    }

    template <RawComponent T_Component>
    dsa::SparseSet<T_Component>& ComponentManager::get_component_storage() {      

        return (*static_cast<ComponentStorage<T_Component>*>(
            // unordered map
            this->_storages[
                dsa::get_type_id<T_Component>()
            ].get()
            // unique_ptr for casting
        ))._storage; // directly return the sparse set
    }

    template <RawComponent... T_Components>
    void ComponentManager::insert(EntityId e, T_Components... components) {
        // Initialize every components of insertion
        this->add_components<T_Components...>();
        // Fold expansion into multiple _insert_one functions
        (this->_insert_one<T_Components>(e, components), ...);
    }

    template <RawComponent... T_Components>
    void ComponentManager::remove(EntityId e) {
        
    }

    template <RawComponent T_Component>
    std::vector<EntityId> ComponentManager::find_entities_for_component() {
        // Create result vector
        auto result = std::vector<EntityId>();
        // get referecence of specific component
        auto& sparse_set = this->get_component_storage<T_Component>();
        for (const auto& i : sparse_set.get_dense_storage()) {
            result.push_back(i.sparse_index);
            // insert entity id for every component.
        }
        return result;
    }

    template <RawComponent... T_Components>
    std::vector<EntityId> ComponentManager::find_archetypes() {
        auto result = std::vector<EntityId>();
        constexpr int TYPE_INTERSECTION_SET_HEIGHT = sizeof...(T_Components);
        std::unordered_map<EntityId, int> temp_map;

        this->add_components<T_Components...>();

        std::array<std::vector<EntityId>, sizeof...(T_Components)> temp{
            this->find_entities_for_component<T_Components>()...
        };

        // iterate over multiple entity sets
        for (auto& entities : temp) {
            // iterate over multiple entity elements per set
            for (EntityId e : entities) {
                // find intersections among all entity sets.
                temp_map[e] += 1;
            }
        }

        for (const auto& pair : temp_map) {
            // if intersection exists among all sets
            if (pair.second == TYPE_INTERSECTION_SET_HEIGHT) {
                // emplace entity id
                result.emplace_back(pair.first);
            }
        }

        return result;
    }
}

namespace ecs {

    template <RawComponent T_Component>
    void ComponentManager::_add_component() {
        const auto type_id = dsa::get_type_id<T_Component>();
        if (!this->_storages.contains(type_id)) {
            // create new sparse set
            this->_storages.emplace(
                type_id,
                std::make_unique<ComponentStorage<T_Component>>()
            );
        }
    }

    template <RawComponent T_Component>
    void ComponentManager::_insert_one(EntityId e, T_Component component) {
        this->get_component_storage<T_Component>().set(e, std::move(component));
    }

}
