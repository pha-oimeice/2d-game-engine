#include <unordered_set>
#include <array>
#include <iostream>

namespace ecs {

    template <QueryComponent... T_Components>
    std::vector<std::tuple<T_Components& ...>> ECSManager::read() {
        auto result = std::vector<
            // tuple made of data with const/ref
            std::tuple<T_Components& ...>>();

        // find all entities for certain composition of components
        auto entities = this->_component_manager.find_archetypes<std::remove_cvref_t<T_Components>...>();

        for (auto e : entities) {
            // tuple construction
            result.emplace_back(
                // cvref is retained here to fetch correct type of component
                this->_component_manager.get_component<T_Components>(e)...
            );
        }

        return result;
    }

    template <QueryResource T_Resource>
    T_Resource& ECSManager::get_resource() {
        return this->_resource_manager.get_resource<T_Resource>();
    }

    template <RawComponent... T_Components>
    EntityId ECSManager::create_entity(T_Components... components) {
        auto id = this->_entity_id_generator.next();
        if constexpr (sizeof...(T_Components) != 0) {
            this->_component_manager.insert<T_Components...>(id, components...);
        }
        return id;
    }
    
}
