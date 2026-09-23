#pragma once
#include "ECSDefinition.hpp"
#include <memory>
#include <unordered_set>
#include <unordered_map>

namespace ecs {
    
    /// @brief Globally unique 
    class ResourceManager final {
    private:

        std::unordered_map<ResourceId, std::unique_ptr<AResource>> _storages;

        template <RawResource T_Resource>
        void _init_resource();

    public:
        
        template <QueryResource T_Resource>
        T_Resource& get_resource();
        
    };
}

#include "ResourceManager.inl"