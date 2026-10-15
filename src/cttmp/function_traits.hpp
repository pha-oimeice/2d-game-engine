#pragma once
#include "type_list.hpp"

namespace cttmp {

    template <typename T>
    struct FunctionTraits {};

    template <typename R, typename... Args>
    struct FunctionTraits<R(*)(Args...)> {
        using Return = R;
        using Arguments = internal::TypeList<Args...>;

        static constexpr std::size_t arity = Arity<Args...>;
    };

    template <typename... Args>
    struct FunctionTraits<void(*)(Args...)> {
        using Arguments = internal::TypeList<Args...>;

        static constexpr std::size_t arity = Arity<Args...>;
    };
}