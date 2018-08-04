//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "fender.hpp"
# include "rendering.hpp"
#include "ChildInfo.hpp"

namespace fender::entities
{
    class GameObject;
}

namespace fender::components {
    struct Children : futils::IComponent {
        std::unordered_map<entities::GameObject *, entities::GameObject *> content;
        void add(entities::GameObject &obj);
        void remove(entities::GameObject &obj);
    };
}

