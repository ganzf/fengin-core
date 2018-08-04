//
// Created by arroganz on 1/13/18.
//

#pragma once

# include "fender.hpp"

namespace fender::components {
    struct Hoverable : futils::IComponent {
        using Action = std::function<void()>;

        Action onHover{[](){}};
        Action onEnter{[](){}};
        Action onLeave{[](){}};

        bool hovered{false};
    };
}