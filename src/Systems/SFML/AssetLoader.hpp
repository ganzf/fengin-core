//
// Created by clara on 1/12/18.
//

#pragma once

# include <SFML/Graphics.hpp>
# include "System.hpp"

namespace fender::systems::SFMLSystems
{
    struct RequestAssets {

    };

    //TODO: Maybe 1 pkg for font and an other one for textures?

    struct AssetsLoaded {
        std::unordered_map<std::string, sf::Texture> *textures;
        std::unordered_map<std::string, sf::Font> *fonts;
    };

    class AssetLoader : public System {
        enum States
        {
            Init = 0,
            Run
        };

        std::unordered_map<std::string, sf::Texture> _textures;
        std::unordered_map<std::string, sf::Font> _fonts;
        void init();

    public:
        AssetLoader(): System("AssetLoader") {}
        void run(float) override;
    };
}

