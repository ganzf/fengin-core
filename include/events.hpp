//
// Created by arroganz on 11/29/17.
//

#ifndef FENGIN_EVENTS_HPP
#define FENGIN_EVENTS_HPP

# include "rendering.hpp"
# include "ecs.hpp"
# include "mediator.hpp"
# include "math.hpp"

namespace fengin::entities
{
    class Camera;
}

namespace fengin::events {
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
        std::function<void(fengin::entities::Camera *)> callback;
    public:
        RequestCamera(std::string const &name, std::function<void(fengin::entities::Camera *)> func):
                name(name), callback(func)
        {

        }

        std::string const &getName() const {
            return name;
        }

        std::function<void(fengin::entities::Camera *)> getCallback() const {
            return callback;
        }
    };

    struct Collision
    {
        futils::IEntity *first;
        futils::IEntity *second;
    };
}

#endif //FENGIN_EVENTS_HPP
