#pragma once
#include <variant>
#include <SFML/Graphics.hpp>
#include "TypeDefinitions.hpp"
#include "ecs/ECS.hpp"

namespace window {

    struct MyShape final : ecs::AComponent {
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

    struct MyText final : ecs::AComponent {
    public:
        sf::Text data;
        explicit inline MyText(const sf::String& string=sf::String(), const sf::Font& font=sf::Font(), unsigned int characterSize = 30)
            : data(string, font, characterSize) {}
    };
}

