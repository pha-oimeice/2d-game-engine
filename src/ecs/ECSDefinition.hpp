#pragma once
#include "TypeDefinitions.hpp"
#include "dsa/SparseSet.hpp"
#include <latch>

namespace ecs {
    using EntityId = td::Id;
    using ComponentId = td::Id;
    using SystemId = td::Id;
    using SystemFn = void(*)();

    constexpr auto MAX_ENTITIES = 1024u;

    // can be used to wait for initialization to complete
    // current multithreading/initialization:
    // - async window thread init : +1
    inline std::latch init_latch{1ull};
}

#include "ECSDefinition.inl"

