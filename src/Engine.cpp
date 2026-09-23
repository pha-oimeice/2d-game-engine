#include "engine.hpp"
#include "components.hpp"
#include "physics/collision.hpp"
#include "my_window/Graphics.hpp"
#include "my_window/Window.hpp"
#include "systems.hpp"
#include <random>
#include <iostream>



namespace engine {

    void setup();
    void run();

    Engine::Engine() {
        
        setup();
        run();
    }

    void setup() {
        srand(114514);
        auto& manager = ecs::get_manager();
        manager.add_system(sys::update_transform);
        manager.add_system(sys::shape_bounce_on_edge);
        manager.add_system(sys::create_enemies);
    }

    void run() {
        auto& window = window::get_window();
        // window::test(); // test passed
        // State 0 : initialization
        ecs::get_manager().init();
        ecs::get_manager().run();
        std::cout << "Hello, World!\n";
        // State 1 : game main loop
        while (window::window_is_open) {
            std::cout << "Current Game Second: " << ecs::game_second << std::endl;
            _sleep(1000);
            ecs::game_second += 1;
        }
    }
}



