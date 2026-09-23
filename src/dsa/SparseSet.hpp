#pragma once
#include "TypeDefinitions.hpp"
#include "algo.hpp"
#include <optional>
#include <vector>

namespace dsa {

    template <typename T>
    class DenseData {
    public:

        td::Id sparse_index;

        T data;

        explicit inline DenseData(td::Id sparse_index=-1, T data=T()) 
            : sparse_index(sparse_index), data(data) {}

    };

    // consistent adapter (get, set)
    template <typename T>
    class SparseSet {
    protected:
        // sparse[id]->index of dense (-1->DNE)
        std::vector<int> _sparse;
        // compact storages
        std::vector<DenseData<T>> _dense;
    public:

        inline SparseSet() : _sparse(std::vector<int>(8, -1)) {}

        // if not found: return nullptr
        DenseData<T> get(td::Id id) const noexcept;

        DenseData<T>* get_ref(td::Id id) noexcept;

        const DenseData<T>* get_ref(td::Id id) const noexcept;

        std::vector<td::Id> get_all_entities() const noexcept;

        const std::vector<DenseData<T>>& get_dense_storage() const noexcept;

        void set(td::Id id, T data);

        void remove(td::Id id) noexcept;

        bool contains(td::Id id) const noexcept;
    };
}



#include "SparseSet.inl"