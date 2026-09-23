#pragma once
#include "dsa/TypeDefinitions.hpp"
#include "dsa/IdGenerator.hpp"
#include "dsa/Vector2.hpp"
#include "InputHandler.hpp"
#include <thread>
#include <unordered_map>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <concepts>
#include <latch>

namespace window
{
    using EventHandler = void(*)(sf::RenderWindow* window, const sf::Event& event);

    inline bool window_is_open = false;

    void test();

    void default_event_handler(
        sf::RenderWindow* window,
        const sf::Event& event
    );

    struct WindowData {
    public:
        explicit WindowData(
            std::string title = "Window", 
            int width = 1280,
            int height = 720,
            int max_fps = 60
        );
        virtual ~WindowData();
		std::string title;
        int width;
        int height;
        int max_fps;
    };

    class Window {
    private:
        std::latch _latch;
        WindowData _wnd_data;
        std::jthread _wnd_thread;
        std::stop_token _wnd_thread_token;
        sf::Font _font;
        sf::RenderWindow _window;
        std::unordered_map<td::Id, std::unique_ptr<sf::Drawable>> _drawables;
        dsa::IdGenerator _drawable_id_manager;
    protected:
        EventHandler _event_handler;
        virtual inline void _draw();
    public:

        explicit Window(
            WindowData wnd_data = WindowData(),
            EventHandler event_handler = default_event_handler
        );
        virtual ~Window() = default;

        void update_window_data(WindowData wnd_data);

        void update_transformable(
            td::Id drawable_id,
            dsa::Transform2 transform
        );

        void update_shape(
            td::Id drawable_id,
            sf::Color color
        );

        void remove_drawable(td::Id drawable_id);

        template <typename T>
        requires (std::derived_from<T, sf::Drawable> && std::derived_from<T, sf::Transformable>)
        td::Id add_drawable(const T drawable);

    };

    inline Window& get_window() {
        window::WindowData windowData("2D Game Engine", 1280, 720, 60);
        static Window MY_WINDOW(
            windowData
        );
        return MY_WINDOW;
    }
}

#include "Window.inl"