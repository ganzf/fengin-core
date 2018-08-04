//
// Created by arroganz on 1/19/18.
//


#pragma once

# include "System.hpp"
# include "Entities/GameObject.hpp"

namespace fender::systems::SFMLSystems {
    class GameObject : public System {
        enum States
        {
            Init = 0,
            Run
        };

        std::unordered_map<components::GameObject *, bool> memory;

        void rec_show(entities::GameObject &);
        void rec_hide(entities::GameObject &);
    public:
        GameObject() : System("GameObject")
        {
            phase = Init;
        }

        void run(float) override;
    };
}

