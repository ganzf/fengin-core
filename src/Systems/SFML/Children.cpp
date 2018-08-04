//
// Created by arroganz on 1/3/18.
//

#include "Entities/GameObject.hpp"
#include "Camera.hpp"
#include "Children.hpp"

namespace fender::systems::SFMLSystems
{
    void Children::rec_updateChildInfo(components::ChildInfo &info)
    {
        if (info.parent != nullptr)
        {
            try {
//                auto &parentIsChild = info.getEntity().get<components::ChildInfo>();
//                if (parentIsChild.parent != nullptr) {
//                    rec_updateChildInfo(parentIsChild);
//                }
            } catch (std::runtime_error const &)
            {
                events->send<std::string>("Reached final parent in ChildSystem rec.");
                return ;
            } // TODO: create your own exception type
            try {
                auto &parent = info.parent->get<components::Transform>();
                auto &self = info.getEntity().get<components::Transform>();
                if (parent.getEntity().has<components::Camera>()) {
                    self.position.x = info.offset.x / 100 * parent.size.w + parent.position.x - parent.size.w / 2;
                    self.position.y = info.offset.y / 100 * parent.size.h + parent.position.y - parent.size.h / 2;
                    self.position.z = parent.position.z - 1;
                } else {
                    self.position.x = info.offset.x / 100 * parent.size.w + parent.position.x;
                    self.position.y = info.offset.y / 100 * parent.size.h + parent.position.y;
                    self.position.z = parent.position.z;
                }
                self.size.w = info.relSize.w / 100 * parent.size.w;
                self.size.h = info.relSize.h / 100 * parent.size.h;
                // TODO : Use info.isGridRelative !
            } catch (std::runtime_error const &) {
                std::cout << "Logical error in [Children] : Element has invalid parent" << std::endl;
            }
        }
    }

    void Children::updateAllChildren()
    {
        auto children = entityManager->get<components::ChildInfo>();
        for (auto child: children)
            rec_updateChildInfo(*child);
    }

    void Children::run(float) {
        switch (phase)
        {
            case Init : return init();
            case Run : return ;
        }
    }

    void Children::init() {
        __init();
        addReaction<StartingRendering>([this](futils::IMediatorPacket &){
            updateAllChildren();
        });
        phase = Run;
    }
}