#include "InputHandler.hpp"

namespace window {

    const sf::Vector2f Controller::get_movement_vector() const {
        float x = this->left    ? -1.f : 0.f + this->right  ? 1.f : 0.f;
        float y = this->up      ? -1.f : 0.f + this->down   ? 1.f : 0.f;
        if (!(x==0.f || y==0.f)) {
            constexpr float FRAC_1_SQRT_2 = 0.70710678118654752440;
            x *= FRAC_1_SQRT_2;
            y *= FRAC_1_SQRT_2;
        }
        return sf::Vector2f(std::move(x), std::move(y));
    }

    const Controller& HardwareInputHandler::get_controller_view() const {
        return *this->_p_controller.get();
    }

    void HardwareInputHandler::set_binding(sf::Keyboard::Key key, ControllerMessage msg) {
        this->_key_bingdings[key] = msg;
    }
    void HardwareInputHandler::set_binding(sf::Mouse::Button key, ControllerMessage msg) {
        this->_mouse_bindings[key] = msg;
    }
    void HardwareInputHandler::remove_binding(sf::Mouse::Button key) {
        this->_mouse_bindings[key] = ControllerMessage::None;
    }
    void HardwareInputHandler::remove_binding(sf::Keyboard::Key key) {
        this->_key_bingdings[key] = ControllerMessage::None;
    }
    void HardwareInputHandler::forward_hardware_input_event(const sf::Event& event) {
        // event filter
        if (event.type != sf::Event::KeyPressed && event.type != sf::Event::KeyReleased) {
            return;
        }
                
        switch (event.type) {
            case sf::Event::MouseMoved:
                (*this->_p_controller.get()).mouse_x = event.mouseButton.x;
                (*this->_p_controller.get()).mouse_y = event.mouseButton.y;
                break;
            case sf::Event::KeyPressed:
            case sf::Event::KeyReleased:
                this->_forward_controller_message(
                    this->_key_bingdings.at(event.key.code),
                    event.type == sf::Event::KeyPressed
                );
                break;
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
                this->_forward_controller_message(
                    this->_mouse_bindings.at(event.mouseButton.button),
                    event.type == sf::Event::MouseButtonPressed
                );
                break;
            default:
                break;
        }
    }

    void HardwareInputHandler::_forward_controller_message(ControllerMessage msg, bool pressed) {
        auto& controller = *this->_p_controller.get();

        auto hold = [pressed](bool& key) {
            key = pressed;
        };
        auto toggle = [pressed](bool key) {
            key = pressed ? !key : key;
        };

        switch (msg) {
            case ControllerMessage::Attack:
                hold(controller.attack);
                break;
            case ControllerMessage::Up:
                hold(controller.up);
                break;
            case ControllerMessage::Down:
                hold(controller.down);
                break;
            case ControllerMessage::Left:
                hold(controller.left);
                break;
            case ControllerMessage::Right:
                hold(controller.right);
                break;
            case ControllerMessage::Pause:
                toggle(controller.pause);
                break;
            default:
                break;
        }
    }
}
