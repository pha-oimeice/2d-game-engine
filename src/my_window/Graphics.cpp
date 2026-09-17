#include "graphics.hpp"
#include "ecs/ECS.hpp"
#include "Window.hpp"
#include <SFML/Graphics.hpp>
#include <variant>

namespace window {
}

namespace window {
    void MyShape::commit_to_renderer() {
        std::visit(
            [this](const auto& shape) {
                using T_Shape = std::remove_cvref_t<decltype(shape)>;
                if constexpr (std::same_as<T_Shape, sf::CircleShape>) {
                    this->id = window::get_window().add_drawable(static_cast<sf::CircleShape>(shape));
                }
                else if constexpr (std::same_as<T_Shape, sf::RectangleShape>) {
                    this->id = window::get_window().add_drawable(static_cast<sf::RectangleShape>(shape));
                }
            },
            this->data
        );
    }
    
    const td::Id MyShape::get_id() const {
        return this->id;
    }

    
}