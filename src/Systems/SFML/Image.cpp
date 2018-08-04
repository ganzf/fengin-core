//
// Created by clara on 1/8/18.
//

#include <Components/Color.hpp>
#include "Image.hpp"
#include "Camera.hpp"
#include "AssetLoader.hpp"

namespace fender::systems::SFMLSystems
{
    void Image::renderImage(components::Image const &image, sf::RenderWindow &window){
        auto &entity = image.getEntity();
        auto &absolute = entity.get<components::AbsoluteTransform>();

        sf::Texture texture = (*_textures)[image.file];
        texture.setSmooth(true);
        sf::RectangleShape sprite;
        sprite.setSize(sf::Vector2f(absolute.size.w, absolute.size.h));
        sprite.setTexture(&texture);
        if (image.size.w != -1 && image.size.h != -1)
            sprite.setTextureRect(sf::Rect(image.position.x, image.position.y, image.size.w, image.size.h));
        sprite.setPosition(absolute.position.x, absolute.position.y);
        if (entity.has<components::Color>()) {
            auto &colorComponent = entity.get<components::Color>();
            sf::Color c;
            c << colorComponent.color;
            sprite.setFillColor(c);
        }
        window.draw(sprite);
    }

    void Image::init() {
        __init();

        addReaction<RenderLayer>([this](futils::IMediatorPacket &pkg){
            if (_textures == nullptr)
                return;
            auto &packet = futils::Mediator::rebuild<RenderLayer>(pkg);
            for (auto &obj: packet.objects)
            {
                if (!obj->has<components::Image>())
                    continue ;
                auto &image = obj->get<components::Image>();
                renderImage(image, *packet.window);
            }
        });

        addReaction<AssetsLoaded>([this](futils::IMediatorPacket &pkg){
            auto &packet = futils::Mediator::rebuild<AssetsLoaded>(pkg);
                _textures = packet.textures;
        });

        events->send<RequestAssets>(RequestAssets());
        phase = Run;
    }

    void Image::run(float) {
        switch (phase)
        {
            case Init: return init();
            case Run: return ;
        }
    }
}
