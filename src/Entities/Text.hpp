//
// Created by clara on 1/11/18.
//

#pragma once

#include <Components/Text.hpp>
#include "GameObject.hpp"

namespace fender::entities
{
    class Text : public GameObject
    {
    public:

        Text(std::string const &s, futils::Vec2<float> pos = {0, 0}, futils::Vec2<float> size = {1, 1}) {
            auto &text = attach<components::Text>();
            setPosition(pos);
            setSize(size);
            text.style.size = 14;
            text.style.color = futils::White;
            text.style.font = "arial.ttf";
            text.str = s;
        }

        void setFont(std::string const &font) {
            auto &text = get<components::Text>();
            text.style.font = font;
        }

        void setColor(futils::Color color) {
            auto &text = get<components::Text>();
            text.style.color = color;
        }

        void setFontSize(int size) {
            auto &text = get<components::Text>();
            text.style.size = size;
        }

        void setTextStyle(std::string const &font, futils::Color color, int size) {
            auto &text = get<components::Text>();
            text.style.size = size;
            text.style.color = color;
            text.style.font = font;
        }

        void setTextStyle(futils::TextStyle const &style) {
            auto &text = get<components::Text>();
            text.style.size = style.size;
            text.style.color = style.color;
            text.style.font = style.font;
        }

        void setText(std::string const &txt) {
            auto &text = get<components::Text>();
            text.str = txt;
        }

        ~Text() {
            detach<components::Text>();
        }
    };
}