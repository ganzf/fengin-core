//
// Created by clara on 1/28/18.
//

#include <Components/Sprite.hpp>
#include "Sprite.hpp"

namespace fender::systems::SFMLSystems {

    void Sprite::update(float elapsed) {
        for (auto &sprite : entityManager->get<fender::components::Sprite>()) {
            if (sprite == nullptr)
                continue;
            if (timeElapsed.find(sprite) != timeElapsed.end()) {
                timeElapsed[sprite] = timeElapsed[sprite] + elapsed;
                continue;
            }
            timeElapsed[sprite] = elapsed;
        }
        for (auto &sprite : entityManager->get<fender::components::Sprite>()) {
            if ( sprite == nullptr || sprite->loop == false)
                continue;
            if (timeElapsed[sprite] > sprite->speed) {
                timeElapsed[sprite] = 0.0;
                sprite->index += 1;
                if (sprite->index >= sprite->files.size())
                    sprite->index = 0;
                if (sprite->getEntity().has<components::Image>()) {
                    auto &img = sprite->getEntity().get<components::Image>();
                    img.file = sprite->files[sprite->index].source;
                    img.position = sprite->files[sprite->index].position;
                    img.size = sprite->files[sprite->index].size;
                }
            }
        }
    }

    void Sprite::init() {
        __init();
        phase = 1;
    }

    void Sprite::run(float elapsed) {
        switch (phase) {
            case 0:
                return init();
            case 1:
                return update(elapsed);
        }
    }
}