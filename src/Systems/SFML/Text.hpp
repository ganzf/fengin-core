//
// Created by clara on 1/11/18.
//

#pragma once

# include <SFML/Graphics.hpp>
# include "System.hpp"
# include "Components/Text.hpp"

namespace fender::systems::SFMLSystems
{
    class Text : public System {
        enum States
        {
            Init = 0,
            Run
        };
        std::unordered_map<std::string, sf::Font> *_fonts = nullptr;
        void renderText(components::Text const &, sf::RenderWindow &);
        void init();

    public:
        Text(): System("Text") {}
        void run(float) override;
    };
}
