#pragma once

namespace engine {
    class Engine;
    class Engine {
    public:
        Engine();
    };
    inline Engine& get_engine() {
        static Engine ENGINE;
        return ENGINE;
    }
}