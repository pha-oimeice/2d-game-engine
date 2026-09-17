#pragma once
#include "TypeDefinitions.hpp"
#include "ecs/ECS.hpp"
#include <thread>
#include <unordered_map>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <concepts>

namespace window
{
    using EventHandler = void(*)(sf::RenderWindow* window, sf::Event event);

    inline bool window_is_open = false;

    void default_event_handler(
        sf::RenderWindow* window,
        sf::Event event
    );

    struct WindowData {
    public:
        WindowData();
        WindowData(std::string title, int width, int height, int max_fps);
        virtual ~WindowData();
		std::string title;
        int width;
        int height;
        int max_fps;
    };

    class Window {
    private:
        WindowData wnd_data;
        std::jthread wnd_thread;
        std::stop_token wnd_thread_token;
        sf::Font font;
        sf::RenderWindow window;
        std::unordered_map<td::Id, std::unique_ptr<sf::Drawable>> drawables;
        dsa::IdGenerator drawable_id_manager;
    protected:
        EventHandler _event_handler;
        virtual inline void _draw();
    public:

        explicit Window(
            WindowData wnd_data = WindowData(),
            EventHandler event_handler = default_event_handler
        );
        virtual ~Window() = default;

        int update_window_data(WindowData wnd_data);

        void update_drawable(td::Id drawable_id, ecs::Transform);

        template <typename T>
        requires (std::derived_from<T, sf::Drawable> && std::derived_from<T, sf::Transformable>)
        td::Id add_drawable(const T& drawable);

    };

    inline Window& get_window() {
        window::WindowData windowData("2D Game Engine", 1280, 720, 60);
        static Window MY_WINDOW(windowData);
        return MY_WINDOW;
    }
}

#include "Window.inl"