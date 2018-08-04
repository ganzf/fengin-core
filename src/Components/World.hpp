//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "fender.hpp"

namespace fender::components {
    struct World : futils::IComponent {
        enum class Type {
            Normal = 0,
            Isometric
        };
        World(Type type = Type::Normal): type(type) {}

        int unit{2};
        vec3f size;
        std::string name;
        Type type;
    };
}



