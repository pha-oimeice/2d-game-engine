#pragma once
#include "dsa/TypeDefinitions.hpp"
#include "PhysicDefinitions.hpp"

namespace components {

    struct PhysicWorldObject {
        td::Id rb_id;
        /// @brief Center Of Mass: a reference to a Transform.translation, the position
        dsa::Vector2f& com;
        /// @brief the offset of com from Transform.translation
        dsa::Vector2f offset;
    };
    
}

namespace controller {
    
    struct MovementController {
        bool up;
        bool down;
        bool left;
        bool right;
        bool grab;
        bool jump;
        bool crouch;
        bool dash;
    }
}

namespace physics {
    
    void add_rule();

    namespace actions {
        
        void bind(td::Id rb_id_a, td::Id rb_id_b);
    }
}