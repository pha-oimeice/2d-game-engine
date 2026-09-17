#include "IdGenerator.hpp"

namespace dsa {

    const td::Id __global_id_generator() {
        static td::Id id = 0u;
        return id++;
    }

    td::Id IdGenerator::next() noexcept{
        if (this->_id_gc.empty()) {
            return this->_next_id++;
        }
        auto id = this->_id_gc.front();
        _id_gc.pop();
        return id;
    }
    void IdGenerator::recycle(td::Id id) noexcept{
        if (id >= this->_next_id) {
            return;
        }
        this->_id_gc.emplace(id);
    }
}