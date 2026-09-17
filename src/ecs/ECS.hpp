#pragma once
#include "ECSDefinition.hpp"
#include "AComponent.hpp"
#include "Transform.hpp"
#include "ECSManager.hpp"
#include "MessageHandler.hpp"

namespace ecs {

    inline bool is_running = true;
    inline unsigned long long game_tick = 0;

    // Query Encapsulation WIP...
    // Query should be temperal
    template <typename... T_Components>
    class Query {
    private:
        std::vector<EntityId> entities;
        std::vector<std::tuple<T_Components&...>> components;
    public:
        Query();
        virtual ~Query() = default;
        const std::vector<EntityId>& get_entities() const;
        const std::vector<std::tuple<T_Components&...>>& get_components() const;
        std::vector<std::tuple<T_Components&...>>& get_components();
    };

    // API WIP...
    template <typename... T_Components>
    Query<T_Components...> read();
}

#include "ECS.inl"

