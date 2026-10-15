#pragma once
#include "dsa/TypeDefinitions.hpp"
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace asset {
    
    struct AssetDescriptor final {

    };

    class AssetManager final {
    public:

    private:

        std::unordered_map<int, AssetDescriptor> _data;

    };

    struct TextureRegistry final {
        // Record external reference to texture
        int reference_count;
        sf::Texture data;
    };

    class TextureManager final {
    public:
    
    private:

        std::unordered_map<td::Id, int> _handle_manager;

        std::unordered_map<td::Id, TextureRegistry> _textures;
    };
}