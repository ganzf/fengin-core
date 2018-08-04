//
// Created by arroganz on 1/13/18.
//


#pragma once

#include <Components/Clickable.hpp>
# include "fender.hpp"
# include "GameObject.hpp"
# include "Components/Editable.hpp"
# include "Components/Text.hpp"
# include "Components/Input.hpp"

namespace {
    std::unordered_map<futils::Keys, char> keys = {
            {futils::Keys::A, 'a'},
            {futils::Keys::B, 'b'},
            {futils::Keys::C, 'c'},
            {futils::Keys::D, 'd'},
            {futils::Keys::E, 'e'},
            {futils::Keys::F, 'f'},
            {futils::Keys::G, 'g'},
            {futils::Keys::H, 'h'},
            {futils::Keys::I, 'i'},
            {futils::Keys::J, 'j'},
            {futils::Keys::K, 'k'},
            {futils::Keys::L, 'l'},
            {futils::Keys::M, 'm'},
            {futils::Keys::N, 'n'},
            {futils::Keys::O, 'o'},
            {futils::Keys::P, 'p'},
            {futils::Keys::Q, 'a'},
            {futils::Keys::R, 'r'},
            {futils::Keys::S, 's'},
            {futils::Keys::T, 't'},
            {futils::Keys::U, 'u'},
            {futils::Keys::V, 'v'},
            {futils::Keys::W, 'w'},
            {futils::Keys::X, 'x'},
            {futils::Keys::Y, 'y'},
            {futils::Keys::Z, 'z'},
            {futils::Keys::Space, ' '},
            {futils::Keys::Num0, '0'},
            {futils::Keys::Num1, '1'},
            {futils::Keys::Num2, '2'},
            {futils::Keys::Num3, '3'},
            {futils::Keys::Num4, '4'},
            {futils::Keys::Num5, '5'},
            {futils::Keys::Num6, '6'},
            {futils::Keys::Num7, '7'},
            {futils::Keys::Num8, '8'},
            {futils::Keys::Num9, '9'},
            {futils::Keys::Dot, '.'},
            {futils::Keys::Comma, ','},
            {futils::Keys::Colon, ':'},
            {futils::Keys::Dash, '-'},
    };

    std::unordered_map<futils::Keys, std::function<void(std::string &)>> advancedKeys = {
            {futils::Keys::Backspace, [](std::string &str){
                str = str.substr(0, str.size() - 1);
            }},
    };

    std::unordered_map<futils::Keys, std::function<void(fender::components::Editable &)>> indexModifiers = {
            {futils::Keys::ArrowLeft, [](fender::components::Editable &editable){
                if (editable.index != 0)
                    editable.index--;
            }},
            {futils::Keys::ArrowLeft, [](fender::components::Editable &editable){
                auto &str = editable.getEntity().get<fender::components::Text>().str;
                if (editable.index < (int)(str.size())) {
                    editable.index += 1;
                } else {
                    editable.index = str.size();
                }
            }},
    };
}

namespace fender::entities {
    class InputField : public GameObject {
        components::Editable *_editable{nullptr};
        components::Text *_text{nullptr};
        components::Input *_inputs{nullptr};
    public:
        InputField(std::string const &placeholder = "") {
            _editable = &attach<components::Editable>();

            _editable->onFocus = [this](){
                this->_inputs->activated = true;
                this->setBorderVisible(true);
                this->borderColor(futils::Lightblue);
            };
            _editable->onFocusLost = [this](){
                this->_inputs->activated = false;
                this->setBorderVisible(false);
            };
            _text = &attach<components::Text>();
            _text->str = placeholder;
            _text->style.font = "earthorbiter.ttf";
            _text->style.size = 18;
            _text->style.color = futils::White;

            _inputs = &attach<components::Input>();
            _inputs->activated = false;
            _inputs->name = "SomeInputField";
            for (auto &pair: keys) {
                char c = pair.second;
                _inputs->map[futils::InputSequence(pair.first)] = [this, c](){
                    _text->str += c;
                    _editable->index++;
                };
            }
            for (auto &pair: advancedKeys) {
                auto func = pair.second;
                _inputs->map[futils::InputSequence(pair.first, futils::InputState::Down)] = [this, func](){
                    func(_text->str);
                };
                _inputs->map[futils::InputSequence(pair.first)] = [this, func](){
                    func(_text->str);
                };
            }
        }
        ~InputField(){
            detach<components::Editable>();
            detach<components::Text>();
        }
        
        void setInputsActivated(bool activated) {
            _inputs->activated = activated;
        }
    };
}


