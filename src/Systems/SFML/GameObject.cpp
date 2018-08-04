//
// Created by arroganz on 1/19/18.
//

#include "GameObject.hpp"
#include "ListView.hpp"
#include "Children.hpp"

namespace fender::systems::SFMLSystems
{
    void GameObject::rec_show(entities::GameObject &obj)
    {
        if (obj.has<components::ListView>()) {
            auto &list = obj.get<components::ListView>();
            for (auto elem: list.content) {
                elem->show();
                if (elem->has<components::ListView>())
                    rec_show(*elem);
            }
        }
    }

    void GameObject::rec_hide(entities::GameObject &obj)
    {
        if (obj.has<components::ListView>()) {
            auto &list = obj.get<components::ListView>();
            for (auto elem: list.content) {
                elem->hide();
                if (elem->has<components::ListView>())
                    rec_hide(*elem);
            }
        }
    }

    void GameObject::run(float) {
        switch (phase) {
            case Init:
                __init();
                phase = Run;
                return ;
            case Run:
                auto gameObjects = entityManager->get<components::GameObject>();
                for (auto &obj: gameObjects) {
                    if (obj->getEntity().has<components::ListView>()) {
                        if (memory.find(obj) == memory.end())
                            memory[obj] = obj->visible;
                        if (obj->visible && !memory[obj]) {
                            rec_show(static_cast<entities::GameObject &>(obj->getEntity()));
                        } else if (!obj->visible && memory[obj]) {
                            rec_hide(static_cast<entities::GameObject &>(obj->getEntity()));
                        }
                        memory[obj] = obj->visible;
                    }
                }
        }
    }
}