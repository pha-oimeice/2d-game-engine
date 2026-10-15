#pragma once
#include <windows.h>

namespace celia {
    class AAI {
    protected:
        unsigned long long previous_tick = 0;
    public:
        virtual void update(unsigned long long this_tick) = 0;
    };

    struct Task {
        unsigned long long deadline;

    };

    template <typename T>
    struct Metric {
    public:
        const T& value;
    };

    class MovementAI : public AAI {
    public:
        void update(unsigned long long this_tick) override {

        }
    };

    class AIRegister {

    };

    class GeneralAI {
    private:
        MovementAI _movement_ai;
    };
}

