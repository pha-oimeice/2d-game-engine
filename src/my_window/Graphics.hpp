#pragma once
#include <variant>
#include <SFML/Graphics.hpp>
#include "dsa/TypeDefinitions.hpp"
#include "ecs/ECS.hpp"

namespace window {

    struct MyShape {
    private:
        using ShapeVarient = std::variant<
            sf::CircleShape,
            sf::RectangleShape
        >;
        td::Id id;
    public:
        ShapeVarient data;
        explicit inline MyShape() : MyShape(sf::CircleShape()) {}
        explicit inline MyShape(sf::CircleShape shape) : data(std::move(shape)) {
            commit_to_renderer();
        }
        explicit inline MyShape(sf::RectangleShape shape) : data(std::move(shape)) {
            commit_to_renderer();
        }
        void commit_to_renderer();
        const td::Id get_id() const;
    };
}

