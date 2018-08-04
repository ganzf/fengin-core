//
// Created by clara on 1/28/18.
//

#pragma once

#include "fender.hpp"

namespace fender::components
{
    class Sprite : public futils::IComponent {
    public:
        std::vector<futils::Image>    files;
        bool loop{true};
        float speed{0.08};
        unsigned int index{0};

        void autoLoad(std::string const &file,
                      futils::Vec2<int> gridNbr,
                      futils::Vec2<int> gridSize)
        {
            int tmpX = 0;
            int tmpY = 0;
            while (tmpY < gridNbr.h) {
                if (tmpX == gridNbr.w) {
                    tmpX = 0;
                    tmpY++;
                } else {
                    addSprite(file, futils::Vec2<int>(tmpX * gridSize.w, gridSize.h * tmpY), gridSize);
                    tmpX++;
                }
            }
        }

        void addSprite(std::string const &file,
                       futils::Vec2<int> pos = futils::Vec2<int>(0, 0),
                       futils::Vec2<int> size = futils::Vec2<int>(-1, -1)) {
            files.emplace_back(file, pos, size);
        }
    };
}