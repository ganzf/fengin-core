//
// Created by clara on 1/11/18.
//

#pragma once

#include "fender.hpp"

namespace fender::components
{
    class Text : public futils::IComponent {
    public:
        futils::TextStyle   style;
        std::string         str;
    };
}