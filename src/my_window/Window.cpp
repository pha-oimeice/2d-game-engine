#include "window.hpp"
#include "dsa/IdGenerator.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace window {

	void test() {
		sf::CircleShape circle(50.f, 5);
		dsa::Transform2 transform(
			dsa::Vector2f(450.f, 150.f)
		);
		td::Id id = get_window().add_drawable(std::move(circle));
		get_window().update_transformable(id, transform);
	}

	void default_event_handler(
		sf::RenderWindow* window,
		const sf::Event& event
	) {
		switch (event.type) {
		// This event triggers when the window is closed
		case sf::Event::EventType::Closed:
			window->close();
			break;
		default:
			// function pointer to handle window message
			// win32 style ?
			break;
		}
	}

	WindowData::WindowData(
		std::string title, 
		int width,
		int height,
		int max_fps
	) : title(title), width(width), height(height), max_fps(max_fps) { }

	WindowData::~WindowData() { }

	Window::Window(
		WindowData wnd_data,
		EventHandler event_handler
	) : _wnd_data(std::move(wnd_data)),
		_event_handler(event_handler),
		_latch(std::latch(1)) {
		// RAII jthread
		// OpenGL: Create window in a dedicated render thread
		this->_wnd_thread = std::jthread(
			[this]
			(std::stop_token token)
		{
			auto& wnd = this->_window;
			auto& font = this->_font;
			auto& wnd_data = this->_wnd_data;
			wnd.create(sf::VideoMode(wnd_data.width, wnd_data.height), wnd_data.title, sf::Style::Default);
			this->update_window_data(wnd_data);
			
			// Attempt to load the font from a file
			font = sf::Font();
			// Main loop - continues for each frame while window is open
			// Games run in an infinite loop!
			std::cout << "Window thread started" << std::endl;
			window::window_is_open = true;
			this->_latch.count_down(1);
			while (wnd.isOpen()) {
				if (token.stop_requested()) {
					wnd.close();
					continue;
				}
				// Event handling
				sf::Event event;
				while (wnd.pollEvent(event)) {
					this->_event_handler(&wnd, event);
				}
				// Basic rendering function calls
				wnd.clear(); // Clear the window of anything previously drawn
				this->_draw(); // Call the draw function to draw the circle and text
				wnd.display(); // Call the window display function
			}
			window::window_is_open = false;
			std::cout << "Window thread terminated\n";
		});
		this->_latch.wait();
	}

	void Window::update_window_data(WindowData new_wnd_data) {
		auto& wnd_data = this->_wnd_data;
		auto& wnd = this->_window;
		wnd_data = std::move(new_wnd_data);

		wnd.setFramerateLimit(wnd_data.max_fps);
		wnd.setSize(sf::Vector2u(wnd_data.width, wnd_data.height));
	}

	void Window::update_transformable(
		td::Id drawable_id,
		dsa::Transform2 transform
	) {
		auto& wnd = this->_window;

		if (!this->_drawables.contains(drawable_id)) {
			std::cout << "Invalid drawable_id: " << drawable_id << std::endl;
			return;
		}
		auto* transformable = dynamic_cast<sf::Transformable*>(this->_drawables.at(drawable_id).get());
		if (transformable == nullptr) {
			std::cout << "ERROR: Drawable Id = " << drawable_id << " is not derived from sf::Transformable.";
			return;
		}
		float screen_x = wnd.getSize().x;
		float screen_y = wnd.getSize().y;
		float p_x = transform.translation.x;
		float p_y = transform.translation.y;
		// These code should be encapsulate in elsewhere?
		transformable->setPosition(sf::Vector2f(p_x, p_y));
		transformable->setRotation(transform.rotation);
		transformable->setScale(sf::Vector2f(transform.scale.x, transform.scale.y));
	}

	void Window::update_shape(
		td::Id drawable_id,
		sf::Color color
	) {
		auto& wnd = this->_window;
		if (!this->_drawables.contains(drawable_id)) {
			std::cout << "Invalid drawable_id: " << drawable_id << std::endl;
			return;
		}

		auto* shape = dynamic_cast<sf::Shape*>(this->_drawables.at(drawable_id).get());
		if (shape == nullptr) {
			std::cout << "ERROR: Drawable Id = " << drawable_id << " is not derived from sf::Shape.";
			return;
		}
		shape->setFillColor(color);
	}

	void Window::remove_drawable(td::Id drawable_id) {
		this->_drawables.erase(drawable_id);
	}

	inline void Window::_draw() {
		auto& wnd = this->_window;

		for (const auto& i : this->_drawables) {
			auto& drawable = *i.second.get();
			wnd.draw(drawable);
		}
	}

	
}
