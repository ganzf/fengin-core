//
// Created by arroganz on 1/3/18.
//

#include "Children.hpp"
#include "Entities/GameObject.hpp"

namespace fender::components
{
    void Children::add(entities::GameObject &obj)
    {
        content.insert(std::pair<entities::GameObject *, entities::GameObject *>(&obj, &obj));
        try {
            auto &childInfo = obj.get<components::ChildInfo>();
            childInfo.parent = &this->getEntity();
        } catch (std::runtime_error const &) {
            auto &childInfo = obj.attach<components::ChildInfo>();
            childInfo.parent = &this->getEntity();
        } // TODO : Create your own exception type
    }

    void Children::remove(entities::GameObject &obj) {
        content.erase(&obj);
        obj.detach<components::ChildInfo>();
    }
}