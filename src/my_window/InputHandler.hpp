#pragma once
#include <bitset>
#include <memory>
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace window {

    void handle_keyboard_input();
    
    enum KeyStatus {
        Pressed,
        Released,
    };

    class AController {
        friend class InputHandler;
    private:
        std::bitset<64> _status;
    protected:
        const bool _get(int index) const noexcept;
    };
    
    class MovementController : public AController {
    public:

        const bool up()     const noexcept;
        const bool down()   const noexcept;
        const bool left()   const noexcept;
        const bool right()  const noexcept;

    };

    class InputHandler {
    private:
        std::unique_ptr<MovementController> _movement_controller;
    public:
        void update_movement_controller();
    };

    enum ControllerMessage {
        None = 0, // default value
        Up,
        Down,
        Left,
        Right,
        Fire,
        Pause,
    };

    class Controller final {
    public:
    
        float mouse_x;
        float mouse_y;

        bool up;
        bool down;
        bool left;
        bool right;
        bool fire;
        bool pause;
        
    };

    class HardwareInputHandler final {
    private:

        std::unique_ptr<Controller> _p_controller;
        std::unordered_map<sf::Mouse::Button, ControllerMessage> _mouse_bindings;
        std::unordered_map<sf::Event::KeyEvent, ControllerMessage> _key_bingdings;

    public:
        explicit inline HardwareInputHandler() : _p_controller(std::make_unique<Controller>()) {}
        virtual ~HardwareInputHandler() = default;
        const Controller& get_controller_view() const;
        void set_binding(sf::Mouse::Button code, ControllerMessage msg);
        void set_binding(sf::Event::KeyEvent key, ControllerMessage msg);
        void remove_binding(sf::Mouse::Button code);
        void remove_binding(sf::Event::KeyEvent key);
        void forward_mouse_event(sf::Event event);
        void forward_key_event(sf::Event event);
    };

    inline HardwareInputHandler& get_hardware_input_handler() {
        static HardwareInputHandler HARDWARE_INPUT_HANDLER;
        return HARDWARE_INPUT_HANDLER;
    }

}