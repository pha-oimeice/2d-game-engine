#include <unordered_set>
#include <array>

namespace ecs {

    template <typename... T_Components>
    std::vector<std::tuple<T_Components& ...>> ECSManager::read() {
        auto result = std::vector<std::tuple<T_Components& ...>>();

        auto entities = *this->_component_manager.find_archetypes<T_Components...>().get();

        return result;
        
        for (EntityId e : entities) {
            result.push_back(
                std::tuple<T_Components&...>{
                    this->_component_manager.get_component<T_Components>(e)...
                }
            );
        }
        return result;
    }

    template <typename... T_Components>
    EntityId ECSManager::create_entity(T_Components... components) {
        auto id = this->_entity_id_generator.next();
        if constexpr (sizeof...(T_Components) != 0) {
            this->_component_manager.insert<T_Components...>(id, components...);
        }
        return id;
    }
    
}
