#pragma once
#include "dsa/TypeDefinitions.hpp"
#include "macros.h"
#include "Abstract.hpp"


namespace ecs {

    using EntityId = td::Id;
    using ComponentId = td::Id;
    using SystemId = td::Id;
    using ResourceId = td::Id;
    using SystemFn = void(*)();
    template <typename... Args>
    using SystemFn1 = void(*)(Args...);
    
    enum class AccessMode {
        Shared,
        Mutex
    };

    template <typename T, AccessMode Mode>
    struct Access {
        using Type = T;
        static constexpr auto Mode = Mode;
    };

    template <typename T>
    using Shared = Access<T, AccessMode::Shared>;

    template <typename T>
    using Mutex = Access<T, AccessMode::Mutex>;

}

#pragma region Concepts
#ifdef CPP_20
#include <concepts>
namespace ecs {
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
#else
#define RawComponent typename
#define RawResource typename
#define QueryComponent typename
#define QueryResource typename
#endif // cpp 20 concept

#pragma endregion