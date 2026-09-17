#include "window.hpp"
#include "ecs/ECS.hpp"
#include "dsa/IdGenerator.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace window
{

	void default_event_handler(
		sf::RenderWindow* window,
		sf::Event event
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

	WindowData::WindowData() : WindowData("Window", 1280, 720, 60) { }
	WindowData::WindowData(std::string title, int width, int height, int max_fps)
		: title(title), width(width), height(height), max_fps(max_fps) { }
	WindowData::~WindowData() { }
	Window::Window(
		WindowData wnd_data,
		EventHandler event_handler
	) : wnd_data(std::move(wnd_data)), _event_handler(event_handler) {

		// RAII jthread
		// OpenGL: Create window in a dedicated render thread
		this->wnd_thread = std::jthread(
			[this]
			(std::stop_token token)
		{
			auto& wnd = this->window;
			auto& font = this->font;
			auto& wnd_data = this->wnd_data;
			wnd.create(sf::VideoMode(wnd_data.width, wnd_data.height), wnd_data.title, sf::Style::Default);
			this->update_window_data(wnd_data);
			
			// Attempt to load the font from a file
			font = sf::Font();
			if (!font.loadFromFile("Audiowide-Regular.ttf")) {
				// If we can't load the font, print an error to the error console and exit
				throw std::runtime_error("Could not load font!");
			}
			// Main loop - continues for each frame while window is open
			// Games run in an infinite loop!
			std::cout << "Window thread started" << std::endl;
			window::window_is_open = true;
			ecs::init_latch.count_down();
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
	}
	int Window::update_window_data(WindowData new_wnd_data) {
		auto& wnd_data = this->wnd_data;
		auto& wnd = this->window;
		wnd_data = std::move(new_wnd_data);

		wnd.setFramerateLimit(wnd_data.max_fps);
		wnd.setSize(sf::Vector2u(wnd_data.width, wnd_data.height));
		
		return 0;
	}

	void Window::update_drawable(td::Id drawable_id, ecs::Transform transform) {
		auto* transformable = dynamic_cast<sf::Transformable*>(&*this->drawables[drawable_id].get());
		if (!transformable) {
			throw "Unreachable! each instance must be derived from both drawable and transformable.";
		}
		// These code should be encapsulate in elsewhere?
		transformable->setPosition(sf::Vector2f(transform.translation.x, transform.translation.y));
		transformable->setRotation(transform.rotation);
		transformable->setScale(sf::Vector2f(transform.scale.x, transform.scale.y));
	}

	

	inline void Window::_draw() {
		auto& wnd = this->window;
		auto test_circle = sf::CircleShape(50.f);

		test_circle.setPosition(sf::Vector2f(400.f,400.f));
		test_circle.setFillColor(sf::Color::Green);
		wnd.draw(test_circle);

		for (const auto& i : this->drawables) {
			wnd.draw(*i.second.get());
		}
	}

	
}
