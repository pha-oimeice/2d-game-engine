#pragma once
#include "AComponent.hpp"
#include "dsa/Vector2.hpp"

namespace ecs {
    struct Transform final : AComponent {
    public:
        explicit inline Transform(
            dsa::Vector2f translation=dsa::Vector2f(0.f, 0.f),
            float rotation=0.f,
            dsa::Vector2f scale=dsa::Vector2f(0.f, 0.f))
            : translation(translation), rotation(rotation), scale(scale) {}
        dsa::Vector2f translation;
        float rotation;
        dsa::Vector2f scale;
    };
}