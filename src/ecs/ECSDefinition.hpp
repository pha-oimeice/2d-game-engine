#pragma once
#include "dsa/TypeDefinitions.hpp"
#include "Abstract.hpp"
#include <concepts>

namespace ecs {
    using EntityId = td::Id;
    using ComponentId = td::Id;
    using SystemId = td::Id;
    using ResourceId = td::Id;
    using SystemFn = void(*)();

    constexpr auto MAX_ENTITIES = 1024u;

    template <typename T>
    concept RawComponent = 
    // component is primitive storage
    !std::is_reference_v<T> &&
    // bad for prefetching
    !std::is_volatile_v<T> &&
    // component should be mutable
    !std::is_const_v<T> &&
    // component should derive from AComponent
    std::derived_from<
        // T should not be const/volatile/reference
        T, AComponent
    >;

    template <typename T>
    concept RawResource = 
    // component is primitive storage
    !std::is_reference_v<T> &&
    // bad for prefetching
    !std::is_volatile_v<T> &&
    // component should be mutable
    !std::is_const_v<T>;

    template <typename T>
    concept QueryComponent =
    // reference is a must, so integrated into query api
    !std::is_reference_v<T> &&
    // bad for prefetching
    !std::is_volatile_v<T> &&
    // definition requirement
    std::derived_from<
        std::remove_cv_t<T>,
        AComponent
    >;

    template <typename T>
    concept QueryResource = 
    // component is primitive storage
    !std::is_reference_v<T> &&
    // bad for prefetching
    !std::is_volatile_v<T>;
}

