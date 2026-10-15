#include "cttmp/function_traits.hpp"

namespace ecs {

    template <typename... T_Args>
    void SystemManager::_add_system(
        const SystemDescriptor<T_Args...>&& system_descriptor
    ) {
        using TFn = cttmp::FunctionTraits<SystemFn1<T_Args...>>;
        using ReturnType = TFn::Return;
        using ArgList = TFn::Arguments;
        if constexpr (!std::same_as<ReturnType, void>) {
            throw "Invalid function signature";
        }
        
    }

    template <typename... T_SystemsDescriptors>
    inline void SystemManager::add_systems(
        const T_SystemsDescriptors&&... system_descriptors
    ) {
        (this->_add_system(system_descriptors), ...);
    }
}