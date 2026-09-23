#pragma once
#include "ECSDefinition.hpp"

namespace ecs {

    class Scheduler {


    public:
        
        template <SystemFn P_FN, int Priority>
        consteval void add_system();
    };
}

/*

Contraints:

1. if a system borrowed a mutable variable, it must run in serial with other systems that uses this variable


*/