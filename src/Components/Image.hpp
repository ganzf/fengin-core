//
// Created by clara on 1/3/18.
//

#pragma once

# include "fender.hpp"

namespace fender::components {
    struct Image : futils::IComponent {
        std::string file;
        vec2i position{0, 0};
        vec2i size{-1, -1};
    };
}