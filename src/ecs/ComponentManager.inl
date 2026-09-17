

namespace ecs {

    template <typename T_Component>
    requires (std::derived_from<T_Component, AComponent>)
    void ComponentManager::add_component() {
        const auto type_id = dsa::get_type_id<T_Component>();
        if (this->_component_registry.contains(type_id)) {
            // create new sparse set

            this->_component_registry.insert(type_id);
        }
    }

    template <typename... T_Components>
    inline void ComponentManager::add_components() {
        (this->add_component<T_Components>(), ...);
    }

    template <typename T_Component>
    requires (std::derived_from<T_Component, AComponent>)
    T_Component& ComponentManager::get_component(EntityId e) {
        auto& sparse_set = this->get_component_storage<T_Component>()._storage;

        auto* data = sparse_set.get_ref(e);
        
        if (data == nullptr) {
            throw "Trying to get component that does not exists.";
        }
        return data->data;
    }

    template <typename T_Component>
    requires (std::derived_from<T_Component, AComponent>)
    ComponentStorage<T_Component>& ComponentManager::get_component_storage() {
        return *static_cast<ComponentStorage<T_Component>*>(
            // unordered map
            this->_storages[
                dsa::get_type_id<T_Component>()
            ].get() // unique_ptr for casting
        );
    }

    template <typename... T_Components>
    void ComponentManager::insert(EntityId e, T_Components... components) {

        // WIP

        this->add_components<T_Components...>();
        (
            /*  1. validate if components is initialized
                2. expand types into individual insertion
            */
            [this, e](auto&& component) {
                using T_Component = std::remove_cvref_t<decltype(component)>;
                // this->get_component_storage<T_Component>().set(e, component);
            }(
                std::forward<T_Components>(components)
            ),
            ...
        );
    }

    template <typename... T_Components>
    void ComponentManager::remove(EntityId e) {
        
    }

    template <typename T_Component>
    requires (std::derived_from<T_Component, AComponent>)
    std::unique_ptr<std::vector<EntityId>> ComponentManager::find_entities_for_component() {
        auto result = std::make_unique<std::vector<EntityId>>();
        auto& storage = this->get_component_storage<T_Component>();
        for (auto i=0; i<sizeof(storage); i++) {
            
        }
        return result;
    }

    template <typename... T_Components>
    std::unique_ptr<std::vector<EntityId>> ComponentManager::find_archetypes() {
        auto result = std::make_unique<std::vector<EntityId>>();
        std::unordered_set<EntityId> temp_set;
        std::array<std::unique_ptr<std::vector<EntityId>>, sizeof...(T_Components)> temp{
            this->find_entities_for_component<T_Components>()...
        };

        for (auto& entities : temp) {
            for (EntityId e : *entities.get()) {
                if (!temp_set.contains(e)) {
                    continue;
                }
                temp_set.emplace(e);
            }
        }

        return result;

        for (EntityId e : temp_set) {
            (*result.get()).emplace_back(e);
        }

        return result;
    }
}
