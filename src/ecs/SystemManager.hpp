#pragma once
#include "ECSDefinition.hpp"
#include "SystemDescriptor.hpp"
#include <initializer_list>
#include <unordered_map>
#include <thread>

namespace ecs {

    enum SystemManagerEnum {
        Idle = 0,
        Initialized = 1,
        Running = 2,
    };

    // Manages System Scheduler, which generates a DAG of execution order for systems.
    // Purpose of this DAG is to altomatically do multithreading.
    class SystemManager final {
    private:

        unsigned int _frame = 0;

        const unsigned int _tick_per_second;

        SystemManagerEnum _status;

        // each function pointer is unique accross application
        std::unordered_map<SystemFn, SystemDescriptor> _system_registry;

        std::unordered_map<SystemFn, std::jthread> _system_threads;

        std::unordered_map<SystemFn, int> _system_tick;
    
    public:

        explicit inline SystemManager(unsigned int tick_per_second=50)
            : _status(SystemManagerEnum::Idle),
              _tick_per_second(tick_per_second) {}

        virtual inline ~SystemManager() { this-> stop(); }

        void add_system(
            const SystemFn system,
            const SystemDescriptor system_desc = SystemDescriptor()
        );

        void init();

        void run();

        void stop();

    };
}


#include "SystemManager.inl"