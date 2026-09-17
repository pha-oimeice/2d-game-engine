
namespace ecs {
    template <typename T_Message>
    void MessageHandler<T_Message>::swap() {
        this->_read->clear();
        std::swap(this->_buf0, this->_buf1);
    }

    template <typename T_Message>
    const std::vector<T_Message>& MessageHandler<T_Message>::read() const {
        return *this->_read;
    }
    template <typename T_Message>
    void MessageHandler<T_Message>::write(T_Message msg) {
        this->_write->emplace_back(std::move(msg));
    }
}