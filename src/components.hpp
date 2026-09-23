#pragma once
#include "dsa/TypeDefinitions.hpp"
#include "dsa/Vector2.hpp"
#include "ecs/Abstract.hpp"

namespace components {

    struct Transform final : ecs::AComponent, public dsa::Transform2 {
    public:
        explicit inline Transform(
            dsa::Vector2f translation=dsa::Vector2f(0.f, 0.f),
            float rotation=0.f,
            dsa::Vector2f scale=dsa::Vector2f(1.f, 1.f))
            : Transform2(translation, rotation, scale) {}
    };

    struct RigidBody final : ecs::AComponent {
    private:
        enum class RBType {
            Static = 0,
            Kinematic = 1,
            Dynamic = 2,
        };
    public:
        explicit inline RigidBody(td::Id id=0, RBType data=RBType::Static) : id(id), data(data) {}
        td::Id id;
        RBType data;
    };

    struct Collider final : ecs::AComponent {
    public:
        explicit inline Collider(float radius=1.0f) : radius(radius) {}
        float radius;
    };

    struct Velocity final : ecs::AComponent {
    public:
        explicit inline Velocity(dsa::Vector2f data=dsa::Vector2f(0.f, 0.f)) : data(data) {}
        dsa::Vector2f data;
    };

    // A n-polygon is made of n points on a circle of radius r
    // where each point apart from their neighber with equal radian 
    struct Polygon final : ecs::AComponent {
    public:
        explicit inline Polygon(
            int n=3,
            float radius=1.f,
            unsigned int rgba=0x00000000
        ) : _id(-1),
            radius(radius),   
            n(n),
            rgba(rgba) {
            if (n<3 || radius<0.f) {
                throw "Invalid polygon";
            }
        }
        int _id;
        float radius;
        int n;
        unsigned int rgba;
    };
    
}