#pragma once
#include "ECSDefinition.hpp"

namespace ecs {

    class SystemDescriptor {
    private:
        
    public:
        const int PRIORITY;
        const char* NAME;
        // unit: tick
        const int COOLDOWN;
        
        explicit inline SystemDescriptor(
            const int priority=0, 
            const char* name="", 
            const int cooldown=1
        ) : PRIORITY(priority), 
            NAME(name),
            COOLDOWN(cooldown)
        {
            if (cooldown < 1) {
                throw "tick per execution cannot be less than 1";
            }
        }
    };
}
