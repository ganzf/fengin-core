//
// Created by clara on 1/10/18.
//


#pragma once

#include <Components/Image.hpp>
#include <Components/Clickable.hpp>
# include "fender.hpp"
# include "GameObject.hpp"
# include "Components/Camera.hpp"
# include "Components/Children.hpp"

namespace fender::entities {
    class Image : public GameObject {
    public:
        Image(std::string const &img, futils::Vec2<float> pos = {0, 0}, futils::Vec2<float> size = {1, 1}) {
            auto &image = attach<components::Image>();
            image.file = img;
            setSize(size);
            setPosition(pos);
        }
        ~Image() {
            detach<components::Image>();
        }

        void setImageFile(std::string const &file) {
            auto &image = get<components::Image>();
            image.file = file;
        }
    };
}