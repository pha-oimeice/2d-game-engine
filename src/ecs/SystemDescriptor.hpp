#pragma once
#include "ECSDefinition.hpp"
#include "cttmp/function_traits.hpp"
#include <stdint.h>
#include <array>

namespace ecs {

    template <typename... T_Args>
    struct SystemDescriptor {
        using Definition = cttmp::FunctionTraits<void(*)(T_Args...)>;
        using Arguments = Definition::Arguments;

        // static constexpr SystemFn1<T_Args...> system;
        std::uint32_t priority;
        std::uint32_t cooldown;
    };

    


    struct SystemDescriptorLegacy {

    };

    

    enum class RelationshipEnum {
        Mutex,
        Order,
    };

}
