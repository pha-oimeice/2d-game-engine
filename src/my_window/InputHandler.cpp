#include "InputHandler.hpp"

namespace window {
    const bool AController::_get(int index) const noexcept {
        if (0 <= index && index <= 63) {
            return this->_status[index];
        }
        return false;
    }

    const Controller& HardwareInputHandler::get_controller_view() const {
        return *this->_p_controller.get();
    }

    void HardwareInputHandler::set_binding(sf::Event::KeyEvent key, ControllerMessage msg) {

    }
    void HardwareInputHandler::set_binding(sf::Mouse::Button code, ControllerMessage msg) {

    }
    void HardwareInputHandler::remove_binding(sf::Mouse::Button code) {

    }
    void HardwareInputHandler::remove_binding(sf::Event::KeyEvent key) {

    }
    void HardwareInputHandler::forward_mouse_event(sf::Event event) {
        if (event.type != sf::Event::MouseButtonPressed) {
            return;
        }
        const auto& msg = this->_mouse_bindings.at(event.mouseButton.button);
        auto& controller = *this->_p_controller.get();
        controller.mouse_x = event.mouseButton.x;
        controller.mouse_y = event.mouseButton.y;
        switch (event.mouseButton.button) {
            case sf::Mouse::Button::Left:
                controller.fire = true;
        }
    }
    void HardwareInputHandler::forward_key_event(sf::Event event) {
        if (event.type != sf::Event::KeyPressed || event.type != sf::Event::KeyReleased) {
            return;
        }
        const auto& msg = this->_key_bingdings.at(event.key);
        auto& controller = *this->_p_controller.get();
        bool pressed = event.type == sf::Event::KeyPressed;
        switch (event.key.code) {
            case sf::Keyboard::W:
                controller.up = pressed;
                break;
            case sf::Keyboard::S:
                controller.down = pressed;
                break;
            case sf::Keyboard::A:
                controller.left = pressed;
                break;
            case sf::Keyboard::D:
                controller.right = pressed;
                break;
            case sf::Keyboard::P:
                controller.pause = pressed ? !controller.pause : controller.pause;
                break;
            default:
                break;
        }
    }
}