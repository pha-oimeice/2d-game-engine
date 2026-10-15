#pragma once
#include "ECSDefinition.hpp"
#include "SystemDescriptor.hpp"
#include "dsa/Graph.hpp"
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
        std::unordered_map<SystemFn, SystemDescriptorLegacy> _system_registry;

        std::unordered_map<SystemFn, std::jthread> _system_threads;
        
        template <typename T_SystemArg>
        void _handle_system_argument() {

        }

        template <typename... T_Args>
        void _add_system(
            const SystemDescriptor<T_Args...>&& system_descriptor
        );
    
    public:

        explicit inline SystemManager(unsigned int tick_per_second=50)
            : _status(SystemManagerEnum::Idle),
              _tick_per_second(tick_per_second) {}

        virtual inline ~SystemManager() { this->stop(); }

        void add_system(
            const SystemFn system,
            const SystemDescriptorLegacy system_desc
        );

        /// @brief Add varidic systems
        /// @tparam ...T_SystemsDescriptors are SystemDescriptor<T_Params...>
        /// @param ...system_descriptors each descriptor contains a void(*)(T_Params...)
        template <typename... T_SystemsDescriptors>
        void add_systems(
            const T_SystemsDescriptors&&... system_descriptors
        );

        void init();

        void run();

        void stop();

    };
}


#include "SystemManager.inl"