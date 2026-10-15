#pragma once
#include <array>    

namespace dsa {

    template <typename T>
    class DenseData {
    public:

        td::Id sparse_index;

        T data;

        explicit inline DenseData(td::Id sparse_index=-1, T data=T()) 
            : sparse_index(sparse_index), data(data) {}

    };

    /// @brief consistent adapter (get, set)
    /// @tparam T should not be reference
    template <typename... Ts>
    class ArchetypeTable {
    protected:
        /// @brief sparse[id]->index of dense (-1->DNE)
        std::vector<td::Id> _sparse;
        /// @brief compact storages
        
        std::tuple<DenseData<Ts>, ...> _dense;
    public:

        inline SparseSet(std::size_t initial_sparse_size = 8) :
            _sparse(std::vector<td::Id>(initial_sparse_size, -1)) {}

        /// @brief get a copy of data T
        /// @param id greater than 0
        /// @return data T, if not found, return T()
        DenseData<T> get(td::Id id) const noexcept;

        /// @brief get a pointer of data T
        /// @param id greater than 0
        /// @return address of data T, if not found: return nullptr
        DenseData<T>* get_ref(td::Id id) noexcept;

        /// @brief get a const pointer of data T
        /// @param id greater than 0
        /// @return const address of data T, if not found: return nullptr
        const DenseData<T>* get_ref(td::Id id) const noexcept;

        /// @brief get all the id that has a dense entity, no allocation
        /// @return a const reference to a vector made of ids
        const std::vector<td::Id> get_all_entities() const;

        /// @brief get reference to dense array
        /// @return a const reference to dense array
        const std::vector<DenseData<T>>& get_dense_storage() const noexcept;

        /// @brief create if id does not exists, overwrite if id exists 
        /// @param id id > 0
        /// @param data T
        void set(td::Id id, T&& data);


        void remove(td::Id id) noexcept;

        bool contains(td::Id id) const noexcept;
    };
}
