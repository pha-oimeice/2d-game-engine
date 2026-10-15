#pragma once
#include "type_list.hpp"

namespace cttmp {

    template <typename... T>
    struct TypeFilter {};

    template <bool WhiteList, typename T, typename T_Filter>
    constexpr bool type_filter() {
        
        using RawT = std::remove_cvref_t<T>;

        static constexpr bool matched = true;

        if constexpr (WhiteList) {
            return matched;
        } else {
            return !matched;
        }
    }
}

