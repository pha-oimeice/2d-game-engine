#pragma once
#include "TypeDefinitions.hpp"
#include <queue>

namespace dsa {

    const td::Id __global_id_generator();

    template <typename T>
    inline const td::Id get_type_id() {
        static const td::Id id = __global_id_generator();
        return id;
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