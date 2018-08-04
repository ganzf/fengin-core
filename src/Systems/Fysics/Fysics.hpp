//
// Created by arroganz on 1/13/18.
//


#pragma once

# include "fender.hpp"

namespace fender::systems
{
    class Fysics : public futils::ISystem
    {
        enum State
        {
            Init = 0,
            Run
        };
        State state{Init};
        void init();
    public:
        Fysics() {
            name = "Fysics";
        }
        void run(float);
    };
}


