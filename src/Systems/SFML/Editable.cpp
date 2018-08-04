//
// Created by arroganz on 1/13/18.
//

#include <inputKeys.hpp>
#include <Components/Text.hpp>
#include <Components/Transform.hpp>
#include <Components/AbsoluteTransform.hpp>
#include "Editable.hpp"

namespace fender::systems::SFMLSystems
{
    void Editable::init() {
        __init();
        addReaction<futils::MouseReleased>([this](futils::IMediatorPacket &pkg){
            auto &mouse = futils::Mediator::rebuild<futils::MouseReleased>(pkg);
            auto editables = entityManager->get<components::Editable>();
            for (auto editable: editables) {
                auto &absolute = editable->getEntity().get<components::AbsoluteTransform>();
                if (mouse.pos.x >= absolute.position.x && mouse.pos.x <= absolute.position.x + absolute.size.w
                    && mouse.pos.y >= absolute.position.y && mouse.pos.y <= absolute.position.y + absolute.size.h) {
                    editable->hasFocus = true;
                } else
                    editable->hasFocus = false;
            }
        });
        addReaction<futils::Keys>([this](futils::IMediatorPacket &pkg){
            auto &key = futils::Mediator::rebuild<futils::Keys>(pkg);
            char letter = -1;
            if (key == futils::Keys::Backspace)
                letter = 0;
            else if (futils::keyToChar.find(key) != futils::keyToChar.end())
                letter = futils::keyToChar.at(key);
            if (letter != -1)
            {
                for (auto &pair: memory)
                {
                    auto &editable = *pair.first;
                    if (editable.hasFocus) {
                        auto &entity = editable.getEntity();
                        auto &text = entity.get<components::Text>();
                        if (letter == 0 && text.str.size() > 0) {
                            text.str = text.str.substr(0, text.str.size() - 1);
                        } else {
                            text.str += letter;
                        }
                    }
                }
            }
        });
        phase = Run;
    }

    void Editable::update(float) {
        auto editables = entityManager->get<components::Editable>();
        for (auto editable: editables) {
            if (editable->hasFocus && !memory[editable])
                editable->onFocus();
            else if (!editable->hasFocus && memory[editable])
                editable->onFocusLost();
            memory[editable] = editable->hasFocus;
        }
    }

    void Editable::run(float f) {
        switch (phase) {
            case Init: return init();
            case Run: return update(f);
        }
    }
}