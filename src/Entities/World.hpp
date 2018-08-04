//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "fender.hpp"
# include "Components/World.hpp"

namespace fender::entities {
    class World : public futils::IEntity {
    public:
        World() {
            attach<components::World>();
        }

        World(std::string const &name, fender::components::World::Type type) {
            auto &world = attach<components::World>(type);
            world.name = name;
        }

        World(std::string const &name, futils::Vec2<float> size = {100, 100}, int unit = 32) {
            auto &world = attach<components::World>();
            world.name = name;
            world.size.w = size.w;
            world.size.h = size.h;
            world.unit = unit;
        }
        ~World() {
            detach<components::World>();
        }

        void setName(std::string const &name) {
            auto &world = get<components::World>();
            world.name = name;
        }

        void setSize(int width, int height) {
            auto &world = get<components::World>();
            world.size.w = width;
            world.size.h = height;
        }

        void setUnit(int unit) {
            auto &world = get<components::World>();
            world.unit = unit;
        }
    };
}

