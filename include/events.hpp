//
// Created by arroganz on 11/29/17.
//

#ifndef FENDER_EVENTS_HPP
#define FENDER_EVENTS_HPP

# include "rendering.hpp"
# include "ecs.hpp"
# include "mediator.hpp"
# include "math.hpp"

namespace fender::entities
{
    class Camera;
}

namespace fender::events {
    struct Alert
    {
        std::string what;
    };

    struct ChangeGridColor
    {
        futils::Color color;
    };

    struct Shutdown // A simple message to shutdown every system in the engine.
    {

    };

    class RequestCamera
    {
        std::string name;
        std::function<void(fender::entities::Camera *)> callback;
    public:
        RequestCamera(std::string const &name, std::function<void(fender::entities::Camera *)> func):
                name(name), callback(func)
        {

        }

        std::string const &getName() const {
            return name;
        }

        std::function<void(fender::entities::Camera *)> getCallback() const {
            return callback;
        }
    };

    struct Collision
    {
        futils::IEntity *first;
        futils::IEntity *second;
    };
}

#endif //FENDER_EVENTS_HPP
