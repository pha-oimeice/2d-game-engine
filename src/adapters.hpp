#pragma once
#include "dsa/TypeDefinitions.hpp"
#include "dsa/Vector2.hpp"
#include "components.hpp"

namespace adapaters {
    
    td::Id upload_polygon_to_renderer(
        float radius,
        int n
    );

    void update_polygon_transform(
        td::Id id,
        dsa::Transform2 transform
    );

    void update_polygon_drawable(
        td::Id id,
        components::Polygon polygon
    );

    void remove_polygon(
        td::Id id
    );
}