//
// Created by arroganz on 1/13/18.
//


#pragma once

# include "fender.hpp"

namespace fender::systems::FysicsSystems {
    class System : public futils::StateSystem {
    protected:
        void __init() {
            addReaction<fender::events::Shutdown>([this](futils::IMediatorPacket &) {
                this->entityManager->removeSystem(name);
            });
        }

    public:
        System(std::string const &systemName) {
            name = "Fysics/" + systemName;
            afterBuild = [this]() {
                __init();
            };
        }

        void run(float) override = 0;
    };
}