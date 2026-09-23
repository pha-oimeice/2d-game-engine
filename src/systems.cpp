#include "systems.hpp"
#include "components.hpp"
#include "ecs/ECS.hpp"
#include "physics/collision.hpp"
#include "my_window/Graphics.hpp"
#include "my_window/Window.hpp"
#include "adapters.hpp"
#include <random>
#include <iostream>

namespace sys {

    void test_system() {
        std::cout << "ECS test system triggered.\n";
    }

    void overlap_detection() {
        using namespace components;
        auto query = ecs::get_manager().read<
            RigidBody,
            Collider,
            Transform,
            Velocity
        >();
        for (auto [rigid_body_a, collider_a, transform_a, velocity_a] : query) {
            for (auto [rigid_body_b, collider_b, transform_b, velocity_b] : query) {
                if (rigid_body_a.id != rigid_body_b.id && (
                    pow(static_cast<double>(transform_a.translation.x-transform_b.translation.x), 2.0) +
                    pow(static_cast<double>(transform_a.translation.y-transform_b.translation.y), 2.0) <
                    pow(static_cast<double>(collider_a.radius+collider_b.radius), 2.0))
                ) {
                    velocity_a.data.x *= -1.0f;
                    velocity_a.data.y *= -1.0f;
                    velocity_b.data.x *= -1.0f;
                    velocity_b.data.y *= -1.0f;
                }
            }
        }
    }

    void update_transform() {
        using namespace components;

        auto query = ecs::get_manager().read<
            Transform,
            Polygon,
            const Velocity
        >();

        // adapaters::remove_polygon(this->id);

        for (auto& [transform, polygon, velocity] : query) {
            // std::cout << "ID = " << polygon._id << ":\n\t" << transform.translation.x << " " << transform.translation.y << "\n";
            if (polygon._id == -1) {
                polygon._id = adapaters::upload_polygon_to_renderer(polygon.radius, polygon.n);
            }

            transform.translation.x += velocity.data.x;
            transform.translation.y += velocity.data.y;

            adapaters::update_polygon_transform(
                polygon._id,
                transform
            );

            // color logic

            unsigned int rgba = rand() << 16 + rand();
            rgba |= 0x000000ff;

            polygon.rgba = rgba;

            adapaters::update_polygon_drawable(
                polygon._id,
                polygon
            );
        }
    }

    void update_shape() {
        using namespace components;

        auto query = ecs::get_manager().read<
            Polygon
        >();

        for (auto& [polygon] : query) {
            if (polygon._id == -1) {
                polygon._id = adapaters::upload_polygon_to_renderer(polygon.radius, polygon.n);
            }
            unsigned int rgba = rand() << 16 + rand();
            rgba |= 0x00000000;

            polygon.rgba = rgba;

            adapaters::update_polygon_drawable(
                polygon._id,
                polygon
            );
        }
        
        _sleep(1000);
    }

    void shape_bounce_on_edge() {
        using namespace components;

        auto query = ecs::get_manager().read<
            Transform,
            const Polygon,
            Velocity
        >();

        for (auto& [transform, polygon, velocity] : query) {
            if ((velocity.data.x > 0.f && transform.translation.x > 1280.f-polygon.radius) ||
                (velocity.data.x < 0.f && transform.translation.x < 0.f+polygon.radius)
            ) {
                transform.translation.x = std::clamp(transform.translation.x, 0.f, 1280.f);
                velocity.data.x *= -1.f;
            }
            if ((velocity.data.y > 0.f && transform.translation.y > 720.f-polygon.radius) ||
                (velocity.data.y < 0.f && transform.translation.y < 0.f+polygon.radius)
            ) {
                transform.translation.y = std::clamp(transform.translation.y, 0.f, 720.f);
                velocity.data.y *= -1.f;
            }
        }
    }

    void create_enemies() {
        using namespace components;
        auto& manager = ecs::get_manager();
        
        auto px = rand() % 1280;
        auto py = rand() % 720;
        auto vx = rand() % 11 + 5;
        auto vy = rand() % 7 + 3;
        auto edge_counts = rand() % 5 + 3;
        auto radius = rand() % 50 + 25;

        manager.create_entity(
            Transform(
                dsa::Vector2f(px, py)
            ),
            Velocity(dsa::Vector2f(vx, vy)),
            Polygon(edge_counts, radius)
        );

        _sleep(1000);
    }

}