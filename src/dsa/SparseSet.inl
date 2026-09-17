
namespace dsa {

    template <typename T>
    DenseData<T> SparseSet<T>::get(td::Id id) const noexcept {
        // does id fall within memory ?
        if (id < 0 || id >= this->_sparse.size()) {
            return DenseData<T>();
        }
        // is id valid ?
        if (this->_sparse[id] < 0) {
            return DenseData<T>();
        }
        return this->_dense[_sparse[id]];
    }

    template <typename T>
    DenseData<T>* SparseSet<T>::get_ref(td::Id id) noexcept {
        // does id fall within memory ?
        if (id < 0 || id >= this->_sparse.size()) {
            return nullptr;
        }
        // is id valid ?
        if (this->_sparse[id] < 0) {
            return nullptr;
        }
        return &this->_dense[_sparse[id]];
    }

    template <typename T>
    const DenseData<T>* SparseSet<T>::get_ref(td::Id id) const noexcept {
        // does id fall within memory ?
        if (id < 0 || id >= this->_sparse.size()) {
            return nullptr;
        }
        // is id valid ?
        if (this->_sparse[id] < 0) {
            return nullptr;
        }
        return &this->_dense[_sparse[id]];
    }

    template <typename T>
    void SparseSet<T>::set(td::Id id, T data) noexcept {
        if (id < 0) {
            return;
        }
        // 1. expand vector to avoid invalid memory access
        if (id >= this->_sparse.size()) {
            auto new_size = std::max(static_cast<size_t>(id+1), _sparse.size() << 1);
            this->_sparse.resize(new_size, -1);
        }
        // 2. if does not exist: insert
        if (this->_sparse[id] < 0) {
            // next dense index
            this->_sparse[id] = this->_dense.size();

            this->_dense.push_back(std::move(DenseData<T>(id, data)));
            // set completed, early return
            return;
        }
        // 3. set value
        this->_dense[_sparse[id]].data = data;
    }

    template <typename T>
    void SparseSet<T>::remove(td::Id id) noexcept {
        if (!this->contains(id)) {
            return;
        }

        const auto dense_index = this->_sparse[id];
        const auto last_dense_index = this->_dense.size() - 1;

        if (dense_index != last_dense_index) {
            
            std::swap(
                this->_dense[dense_index],
                this->_dense[last_dense_index]
            );

            this->_sparse[this->_dense[dense_index].sparse_index] = dense_index;
        }

        // reduce vector.size() by 1
        this->_dense.pop_back();
        this->_sparse[id] = -1;
    }

    template <typename T>
    bool SparseSet<T>::contains(td::Id id) const noexcept{
        return !(this->get_ref(id)==nullptr);
    }

    template <typename T>
    std::vector<td::Id> SparseSet<T>::get_all_entities() const noexcept {
        auto result = std::vector<td::Id>(this->_dense.size(), 0);
        for (const auto& i : this->_dense) {
            result.emplace_back(i.sparse_index);
        }
        return result;
    }

    template <typename T>
    const std::vector<DenseData<T>>& SparseSet<T>::get_dense_storage() const noexcept{
        return this->_dense;
    }
}
