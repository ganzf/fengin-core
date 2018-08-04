//
// Created by arroganz on 1/13/18.
//

#include <Components/Transform.hpp>
#include "RigidBody.hpp"

namespace fender::systems::FysicsSystems
{
    void RigidBody::init() {
        phase = Run;
        addReaction<fender::events::Shutdown>([this](futils::IMediatorPacket &){
            entityManager->removeSystem(name);
        });
    }

    void RigidBody::update(float elapsed)
    {
        auto bodies = entityManager->get<components::rigidBody>();
        for (auto body: bodies)
        {
            auto &pos = body->getEntity().get<components::Transform>();
            pos.position.y += elapsed * body->force.y;
            pos.position.x += elapsed * body->force.x;
        }
    }

    void RigidBody::run(float elapsed) {
        switch (phase)
        {
            case Init: return init();
            case Run: return update(elapsed);
        }
    }
}