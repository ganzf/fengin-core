//
// Created by clara on 1/24/18.
//


#pragma once

# include "System.hpp"
# include "Components/rigidBody.hpp"

namespace fender::systems::FysicsSystems
{
    class Collision : public System {

        void detectCollisions() const;

    public:
        Collision() : System("Collision") {}
        void run(float) override;
    };
}