#include "dsa/IdGenerator.hpp"
#include <iostream>

namespace window {

    template <typename T>
    requires (std::derived_from<T, sf::Drawable> && std::derived_from<T, sf::Transformable>)
    td::Id Window::add_drawable(const T& drawable) {
		auto id = this->drawable_id_manager.next();
		this->drawables.emplace(id, std::make_unique<T>(drawable));
		return id;
	}
}