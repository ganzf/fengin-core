//
// Created by arroganz on 1/20/18.
//


#pragma once

#include <Components/Color.hpp>
# include "fender.hpp"
# include "GameObject.hpp"
# include "Components/Bar.hpp"

namespace fender::entities
{
    class Bar : public GameObject {
        components::Bar *_bar{nullptr};
        components::Color *_color{nullptr};
    public:
        Bar(futils::Color color = futils::Transparent) {
            _bar = &attach<components::Bar>();
            _color = &attach<components::Color>();
            _color->color = color;
            setBorderVisible(true);
        }
    };
}

