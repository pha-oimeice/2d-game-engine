#pragma once
#include <string>

namespace asset {
    
    enum class AnimationState {
        Idle,
        Stand,
        Walk,
        Run,
        Fall,
        Attack,
    };

    struct AnimationDescriptor final {
        AnimationState state = AnimationState::Idle;
        std::string name;
        int frames = 1;
        bool passive_loop = false;
    };

    struct SpriteDescriptor {
        std::string texture_filename;
        int x_offset_unit;
        int y_offset_unit;
    };
 
    class AnimationStateMachine {
    public:
        
        void invoke(AnimationState state);
    };

    class IAnimation {
    public:
        virtual void idle() = 0;
        virtual void stand() = 0;
        virtual void walk() = 0;
        virtual void run() = 0;
        virtual void fall() = 0;
        virtual void attack() = 0;
    };
}