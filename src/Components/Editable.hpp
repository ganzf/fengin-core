//
// Created by arroganz on 1/13/18.
//


#pragma once

# include "fender.hpp"

namespace fender::components {
    struct Editable : futils::IComponent {
        bool hasFocus{false};
        std::function<void()> onFocus{[](){}};
        std::function<void()> onFocusLost{[](){}};
        int index{0};
    };
}

