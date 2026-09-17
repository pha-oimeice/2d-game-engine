#include "ECSManager.hpp"
#include <iostream>

namespace ecs
{
    
    void ECSManager::remove_entity(EntityId entity) {
        
    }

    void ECSManager::init() {
        this->_system_manager.init();
    }

    void ECSManager::run() {
        this->_system_manager.run();
    }
    
    void ECSManager::stop() {
        this->_system_manager.stop();
    }

    void ECSManager::add_system(
        const SystemFn system,
        const SystemDescriptor system_desc
    ) {
        this->_system_manager.add_system(std::move(system), std::move(system_desc));
    }
}
