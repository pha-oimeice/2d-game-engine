#pragma once
#include "TypeDefinitions.hpp"
#include <queue>

namespace dsa {

    const td::Id __global_id_generator();

    template <typename T>
    constexpr inline char TYPE_TOKEN = 0;

    template <auto P_Fn>
    constexpr inline char FUNCTION_TOKEN = 0;

    template <typename T>
    const inline td::Id get_type_id() {
        const static td::Id id = __global_id_generator();
        return id;
    }

    template <typename T>
    constexpr inline void* get_type_id_1() {
        return &TYPE_TOKEN<T>;
    }

    template <auto P_Fn>
    constexpr inline void* get_fn_id() {
        return &FUNCTION_TOKEN<P_Fn>;
    }

    class IdGenerator {
    private:
        td::Id _next_id = 0u;
        std::queue<td::Id> _id_gc;
    public:
        td::Id next() noexcept;
        void recycle(td::Id id) noexcept;
    };
}

#include "IdGenerator.inl"