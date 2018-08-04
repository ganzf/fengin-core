//
// Created by arroganz on 1/13/18.
//


#pragma once

# include "fender.hpp"

namespace fender::components {
    struct rigidBody : futils::IComponent {
        float weight;
        vec3f force;
    };
}


