#include "SystemManager.hpp"
#include <iostream>
#include <latch>
#include <thread>

namespace ecs {
    void SystemManager::add_system(
        const SystemFn system,
        const SystemDescriptor system_desc
    ) {
        if (this->_status != Idle) {
            return;
        }
        this->_system_registry.emplace(system, system_desc);
    }

    void SystemManager::init() {
        if (this->_status == SystemManagerEnum::Idle) {

            // ...
            
            this->_status = SystemManagerEnum::Initialized;
        }
    }

    void SystemManager::run() {
        if (this->_status == SystemManagerEnum::Initialized) {

            for (const auto& sys : this->_system_registry) {
                const auto& sys_fn = sys.first;
                const auto exec_cooldown = 1000 / this->_tick_per_second;
                this->_system_threads.emplace(
                    sys_fn,
                    std::jthread(
                        [sys_fn, exec_cooldown]
                        (std::stop_token token)
                    {
                        do {
                            sys_fn();                        
                            // Synchronization
                            _sleep(exec_cooldown);
                        } while (!token.stop_requested());
                    })
                );
            }

            this->_status = SystemManagerEnum::Running;
        }
    }

    void SystemManager::stop() {
        if (this->_status == SystemManagerEnum::Initialized) {
            this->_status = Idle;
            return;
        }
        if (this->_status == SystemManagerEnum::Running) {
        
            for (auto& sys : this->_system_threads) {
                auto& sys_thread = sys.second;
                sys_thread.request_stop();
            }

            this->_status = SystemManagerEnum::Idle;
        }
        
    }
}