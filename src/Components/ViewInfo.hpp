//
// Created by arroganz on 1/16/18.
//


#pragma once

#include "ecs.hpp"

namespace fender::components {
    struct ViewInfo : futils::IComponent {
        // Ajouter valign, align, etc...
        float h;
        float w;
    };
}


