#include "adapters.hpp"
#include "my_window/Window.hpp"
#include <iostream>

namespace adapaters {
    td::Id upload_polygon_to_renderer(
        float radius,
        int n
    ) {
        auto shape = sf::CircleShape(radius, n);
        shape.setOrigin(sf::Vector2f(radius, radius));
        shape.setFillColor(sf::Color::White);
        shape.setOutlineColor(sf::Color::Cyan);
        shape.setOutlineThickness(5.f);

        auto id = window::get_window().add_drawable(std::move(shape));
        return id;
    }

    void update_polygon_transform(
        td::Id id,
        dsa::Transform2 transform
    ) {
        window::get_window().update_transformable(
            id, 
            std::move(transform)
        );
    }

    void update_polygon_drawable(
        td::Id id,
        components::Polygon polygon
    ) {

        window::get_window().update_shape(
            id,
            sf::Color(polygon.rgba)
        );
    }

    void remove_polygon(
        td::Id id
    ) {
        window::get_window().remove_drawable(id);
    }
}