#pragma once
#include "ECSDefinition.hpp"

namespace ecs {

    class SystemDescriptor {
    private:
        
    public:
        const unsigned int PRIORITY;
        const char* NAME;
        const unsigned int TICK_PER_EXEC;
        
        explicit inline SystemDescriptor(
            const unsigned int priority=0u, 
            const char* name="", 
            const unsigned int tick_per_exec=1u
        ) : PRIORITY(priority), 
            NAME(name),
            TICK_PER_EXEC(tick_per_exec)
        {
            if (tick_per_exec < 1) {
                throw "tick per execution cannot be less than 1";
            }
        }
    };
}
