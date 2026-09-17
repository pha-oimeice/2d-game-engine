#include "engine.hpp"
#include "physics/collision.hpp"
#include "my_window/Graphics.hpp"
#include "my_window/Window.hpp"
#include "systems/tests.hpp"
#include <iostream>

void assignment_1();

namespace engine {
    Engine::Engine() {
        assignment_1();
        run();
    }

    void run() {
        auto& window = window::get_window();
        // State 0 : initialization
        ecs::get_manager().add_system(sys::test_system);
        ecs::get_manager().init();
        ecs::get_manager().run();
        ecs::init_latch.wait();
        std::cout << "Hello, World!\n";
        // State 1 : game main loop
        while (window::window_is_open) {
            std::cout << "Current Game Tick: " << ecs::game_tick << std::endl;
            _sleep(1000);
            ecs::game_tick += 1;
        }
    }
}

void assignment_1() {
    auto& manager = ecs::get_manager();
    
    auto circle1 = sf::CircleShape(50.f);
    circle1.setFillColor(sf::Color::Blue);
    circle1.setPosition(sf::Vector2f(550.f, 200.f));

    auto rect1 = sf::RectangleShape(sf::Vector2f(100.f, 100.f));
    rect1.setFillColor(sf::Color::Red);
    rect1.setPosition(sf::Vector2f(100.f, 50.f));

    auto entities = std::initializer_list<ecs::EntityId>{
        manager.create_entity(
            ecs::Transform(),
            physics::RigidBody(),
            physics::Collider(),
            physics::Velocity(),
            window::MyShape(circle1)
        ),
        manager.create_entity(
            ecs::Transform(),
            window::MyShape(rect1)
        )
    };
    for (auto e : entities) {
        std::cout << e << ' ';
    }
    std::cout << std::endl;
}

