//
// Created by arroganz on 1/13/18.
//


#pragma once

#include <Components/Editable.hpp>
#include <Components/Border.hpp>
#include "System.hpp"

namespace fender::systems::SFMLSystems {
    class Editable : public System {
        std::unordered_map<components::Editable *, bool> memory;

        enum States
        {
            Init = 0,
            Run,
        };
        void update(float);
        void init();
    public:
        Editable() : System("Editable") {}
        void run(float) override;
    };
}

