//
// Created by clara on 1/11/18.
//

#pragma once

# include <SFML/Graphics.hpp>
# include "System.hpp"
# include "Components/Clickable.hpp"

namespace fender::systems::SFMLSystems
{
    class Clickable : public System {
        enum States
        {
            Init = 0,
            Run
        };
        //void renderBorder(components::Border const &, sf::RenderWindow &);
        void init();
        //bool shouldPrint; // debug only
    public:
        Clickable(): System("Clickable") {}
        void run(float) override;
    };
}
