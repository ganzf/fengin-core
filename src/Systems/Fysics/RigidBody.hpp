//
// Created by arroganz on 1/13/18.
//


#pragma once

# include "System.hpp"
# include "Components/rigidBody.hpp"

namespace fender::systems::FysicsSystems
{
    class RigidBody : public System {
        int phase{0};
        enum States
        {
            Init = 0,
            Run
        };

        void update(float);
        void init();
    public:
        RigidBody() : System("RigidBody") {}
        void run(float) override;
    };
}

