//
// Created by arroganz on 1/5/18.
//


#pragma once

# include "fender.hpp"
# include "rendering.hpp"

namespace fender::components
{
    struct Border : futils::IComponent
    {
        bool right{true};
        bool left{true};
        bool up{true};
        bool down{true};
        bool visible;
        futils::Color color;
        int thickness{1};
    };
}

