//
// Created by arroganz on 1/13/18.
//


#pragma once

# include "System.hpp"

namespace fender::systems::SFMLSystems
{
    class Hoverable : public System
    {
        enum States
        {
            Init = 0,
            Run
        };

        void init();
        void update(futils::MouseMoved const &);
    public:
        Hoverable() : System("Hoverable") {}
        void run(float) override;
    };
}