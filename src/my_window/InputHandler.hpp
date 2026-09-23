#pragma once
#include <memory>
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace window {
    enum class ControllerMessage {
        None = 0, // default value
        Up,
        Down,
        Left,
        Right,
        Attack,
        Pause,
    };

    class Controller final {
        friend class HardwareInputHandler;
    private:

    public:
        
        float mouse_x;
        float mouse_y;

        bool up;
        bool down;
        bool left;
        bool right;
        bool attack;
        bool pause;

        // The magnitude of the vector is guranteed to be about 1.0f
        const sf::Vector2f get_movement_vector() const;
    };

    class HardwareInputHandler final {
    private:

        std::unique_ptr<Controller> _p_controller;
        std::unordered_map<sf::Mouse::Button, ControllerMessage> _mouse_bindings;
        std::unordered_map<sf::Keyboard::Key, ControllerMessage> _key_bingdings;

        void _forward_controller_message(ControllerMessage msg, bool pressed);

    public:
        explicit inline HardwareInputHandler() : _p_controller(std::make_unique<Controller>()) {}
        virtual ~HardwareInputHandler() = default;
        const Controller& get_controller_view() const;
        void set_binding(sf::Mouse::Button key, ControllerMessage msg);
        void set_binding(sf::Keyboard::Key key, ControllerMessage msg);
        void remove_binding(sf::Mouse::Button key);
        void remove_binding(sf::Keyboard::Key key);
        void forward_hardware_input_event(const sf::Event& event);
    };

    /// @brief This is all you need for input handling, api are encapsulated
    /// @return 
    inline HardwareInputHandler& get_hardware_input_handler() {
        static HardwareInputHandler HARDWARE_INPUT_HANDLER;
        return HARDWARE_INPUT_HANDLER;
    }
}