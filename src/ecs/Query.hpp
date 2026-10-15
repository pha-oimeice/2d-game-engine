#pragma once
#include "ECSDefinition.hpp"
#include <vector>
#include <tuple>

namespace ecs {

    namespace internal {

        class AQuery {};

    }


    /// @brief  Query is generated in compile time.
    /// 
    /// - Generation: generated in compile time if it is included as a parameter for system.
    /// 
    /// - Lifetime: static
    ///
    /// - Access: Internal
    /// 
    /// @tparam ...T_Components 
    template <QueryComponent... T_Components>
    class Query : public internal::AQuery {
    private:
        /// @brief result entity id set for this certain composition of components
        std::vector<EntityId> _entities;
        /// @brief result component composition reference
        std::vector<std::tuple<T_Components&...>> _components;
    public:
        const std::vector<EntityId>& get_entities() const;

        /// @brief get reference to vector
        /// @return vector has static lifetime, pooling
        std::vector<std::tuple<T_Components&...>>& read();
        /// @brief const version of read() 
        const std::vector<std::tuple<T_Components&...>>& read() const;

        /// @brief get reference to components belong to certain entity
        /// @param e entity_id
        /// @return tuple pointer or nullptr if e does not exist
        std::tuple<T_Components&...>* get(EntityId e);
        /// @brief const version of get(e) 
        const std::tuple<T_Components&...>* get(EntityId e) const;
    };
}
