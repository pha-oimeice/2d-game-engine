#pragma once
#include <array>
#include <concepts>
#include <utility>

namespace cttmp {

    namespace internal {

        template <typename... Ts>
        struct TypeList {};

        template <typename T>
        struct TypeListArity {};

        template <std::size_t Index, typename T_List>
        struct _TypeAt;

        template <typename T_List, std::size_t... Indices>
        struct TypeAt {};

        template <typename T>
        struct ToTypeList {};

        template <template <typename...> class T_Class, typename... Ts>
        struct ToTypeList<T_Class<Ts...>> {
            using type = TypeList<Ts...>;
        };

        template <std::size_t Index, typename... Ts>
        struct _TypeAt<Index, TypeList<Ts...>> {
            using type =
                std::tuple_element_t<
                    Index,
                    std::tuple<Ts...>
                >;
        };

        template <typename T_List, std::size_t Index, std::size_t... RestIndices>
        struct TypeAt<T_List, Index, RestIndices...> {
            using type =
            // Use indices recursively
                typename TypeAt<
                    _TypeAt<Index, T_List>,
                    RestIndices...
                >::type;
        };
        
        template <typename T_List>
        struct TypeAt<T_List> {
            // End of Recursion
            using type = T_List;
        };

        template <typename... Ts>
        struct TypeListArity<internal::TypeList<Ts...>>
        // Inheritance
            : public std::integral_constant<
                std::size_t,
                sizeof...(Ts)
            >
        {};
    }

    template <typename List, std::size_t... Indices>
    using TypeAt = typename internal::TypeAt<List, Indices...>::type;
    
    template <typename T_List>
    inline constexpr std::size_t Arity = internal::TypeListArity<T_List>::value;
}