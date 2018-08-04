//
// Created by arroganz on 1/8/18.
//


#pragma once

# include "fender.hpp"
# include "rendering.hpp"

namespace fender::entities
{
    class GameObject;
}

namespace fender::components {
    struct ChildInfo : futils::IComponent {
        vec3f offset;
        vec3f relSize;
        bool isGridRelative{false};
        futils::IEntity *parent{nullptr};
    };
}

