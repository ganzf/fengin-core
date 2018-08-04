//
// Created by arroganz on 1/1/18.
//

#pragma once

# include "System.hpp"
# include "Components/Input.hpp"

namespace fender::systems::SFMLSystems
{
    class Input : public System
    {
        using Component = components::Input;
        using Sequence = futils::InputSequence;

        std::unordered_map<futils::Keys, futils::InputState>  _keyState = {
                {futils::Keys::Undefined, futils::InputState::Undefined},
                {futils::Keys::A, futils::InputState::Up},
                {futils::Keys::B, futils::InputState::Up},
                {futils::Keys::C, futils::InputState::Up},
                {futils::Keys::D, futils::InputState::Up},
                {futils::Keys::E, futils::InputState::Up},
                {futils::Keys::F, futils::InputState::Up},
                {futils::Keys::G, futils::InputState::Up},
                {futils::Keys::H, futils::InputState::Up},
                {futils::Keys::I, futils::InputState::Up},
                {futils::Keys::J, futils::InputState::Up},
                {futils::Keys::K, futils::InputState::Up},
                {futils::Keys::L, futils::InputState::Up},
                {futils::Keys::M, futils::InputState::Up},
                {futils::Keys::N, futils::InputState::Up},
                {futils::Keys::O, futils::InputState::Up},
                {futils::Keys::P, futils::InputState::Up},
                {futils::Keys::Q, futils::InputState::Up},
                {futils::Keys::R, futils::InputState::Up},
                {futils::Keys::S, futils::InputState::Up},
                {futils::Keys::T, futils::InputState::Up},
                {futils::Keys::U, futils::InputState::Up},
                {futils::Keys::V, futils::InputState::Up},
                {futils::Keys::W, futils::InputState::Up},
                {futils::Keys::X, futils::InputState::Up},
                {futils::Keys::Y, futils::InputState::Up},
                {futils::Keys::Z, futils::InputState::Up},
                {futils::Keys::F1, futils::InputState::Up},
                {futils::Keys::F2, futils::InputState::Up},
                {futils::Keys::F3, futils::InputState::Up},
                {futils::Keys::F4, futils::InputState::Up},
                {futils::Keys::F5, futils::InputState::Up},
                {futils::Keys::F6, futils::InputState::Up},
                {futils::Keys::F7, futils::InputState::Up},
                {futils::Keys::F8, futils::InputState::Up},
                {futils::Keys::F9, futils::InputState::Up},
                {futils::Keys::F10, futils::InputState::Up},
                {futils::Keys::F11, futils::InputState::Up},
                {futils::Keys::F12, futils::InputState::Up},
                {futils::Keys::ArrowUp, futils::InputState::Up},
                {futils::Keys::ArrowDown, futils::InputState::Up},
                {futils::Keys::ArrowLeft, futils::InputState::Up},
                {futils::Keys::ArrowRight, futils::InputState::Up},
                {futils::Keys::Return, futils::InputState::Up},
                {futils::Keys::Backspace, futils::InputState::Up},
                {futils::Keys::Space, futils::InputState::Up},
                {futils::Keys::Escape, futils::InputState::Up},
                {futils::Keys::Delete, futils::InputState::Up},
                {futils::Keys::Tab, futils::InputState::Up},
                {futils::Keys::LCtrl, futils::InputState::Up},
                {futils::Keys::RCtrl, futils::InputState::Up},
                {futils::Keys::LShift, futils::InputState::Up},
                {futils::Keys::RShift, futils::InputState::Up},
                {futils::Keys::Alt, futils::InputState::Up},
                {futils::Keys::Num0, futils::InputState::Up},
                {futils::Keys::Num1, futils::InputState::Up},
                {futils::Keys::Num2, futils::InputState::Up},
                {futils::Keys::Num3, futils::InputState::Up},
                {futils::Keys::Num4, futils::InputState::Up},
                {futils::Keys::Num5, futils::InputState::Up},
                {futils::Keys::Num6, futils::InputState::Up},
                {futils::Keys::Num7, futils::InputState::Up},
                {futils::Keys::Num8, futils::InputState::Up},
                {futils::Keys::Num9, futils::InputState::Up},
                {futils::Keys::RShift, futils::InputState::Up},
                {futils::Keys::PageUp, futils::InputState::Up},
                {futils::Keys::PageDown, futils::InputState::Up},
                {futils::Keys::Quote, futils::InputState::Up},
                {futils::Keys::Dash, futils::InputState::Up},
                {futils::Keys::LBracket, futils::InputState::Up},
                {futils::Keys::RBracket, futils::InputState::Up},
                {futils::Keys::SemiColon, futils::InputState::Up},
                {futils::Keys::Comma, futils::InputState::Up},
                {futils::Keys::Slash, futils::InputState::Up},
                {futils::Keys::BackSlash, futils::InputState::Up},
                {futils::Keys::LButton, futils::InputState::Up},
                {futils::Keys::RButton, futils::InputState::Up},
                {futils::Keys::MouseWheelButton, futils::InputState::Up},
                {futils::Keys::JoystickA, futils::InputState::Up},
                {futils::Keys::JoystickB, futils::InputState::Up},
                {futils::Keys::JoystickX, futils::InputState::Up},
                {futils::Keys::JoystickY, futils::InputState::Up},
        };

        enum States
        {
            Init = 0,
            Run
        };

        void checkInputs();
        void reset();
        void process(sf::Event const &event);
        void init();
    public:
        Input() : System("Input") {}
        void run(float) override;
    };
}
