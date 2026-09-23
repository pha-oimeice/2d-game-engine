#include "dsa/IdGenerator.hpp"

namespace ecs {

    template <RawResource T_Resource>
    void ResourceManager::_init_resource() {
        const auto type_id = dsa::get_type_id<T_Resource>();
        if (!this->_storages.contains(type_id)) {
            // create new resource
            this->_storages.emplace(
                type_id,
                std::make_unique<AResource>()
            );
        }
    }

    template <QueryResource T_Resource>
    T_Resource& ResourceManager::get_resource() {
        using T_RawResource = std::remove_cvref_t<T_Resource>;

        this->_init_resource<T_RawResource>();

        return *static_cast<T_RawResource*>(
            this->_storages[
                dsa::get_type_id<T_RawResource>()
            ].get()
        );
    }
}