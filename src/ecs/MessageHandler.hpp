#pragma once
#include <vector>

namespace ecs {
    template <typename T_Message>
    class MessageHandler {
    private:
        std::vector<T_Message> _buf0;
        std::vector<T_Message> _buf1;
        std::vector<T_Message>* _read;
        std::vector<T_Message>* _write;
    protected:
        void swap();
    
    public:
        const std::vector<T_Message>& read() const;
        void write(T_Message);
    };

    template <typename T_Message>
    T_Message& get_message_handler() {
        static MessageHandler MESSAGE_HANDLER;
        return MESSAGE_HANDLER;
    }
}

#include "MessageHandler.inl"