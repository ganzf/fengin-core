//
// Created by arroganz on 1/7/18.
//

#include "inputKeys.hpp"
#include "Border.hpp"
#include "Camera.hpp"

namespace fender::systems::SFMLSystems
{
    void Border::renderBorder(components::Border const &border, sf::RenderWindow &window)
    {
        auto &absolute = border.getEntity().get<components::AbsoluteTransform>();
        sf::RectangleShape shape;
        sf::Color color;
        color << border.color;
        if (border.up && border.down && border.left && border.right) {
            shape.setFillColor(sf::Color::Transparent);
            shape.setOutlineThickness(border.thickness);
            shape.setOutlineColor(color);
            shape.setSize(sf::Vector2f(absolute.size.w, absolute.size.h));
            shape.setPosition(absolute.position.x, absolute.position.y);
            window.draw(shape);
        } else {
            sf::RectangleShape line;
            line.setFillColor(color);
            if (border.up) {
                line.setPosition(absolute.position.x, absolute.position.y - border.thickness);
                line.setSize(sf::Vector2f(absolute.size.w, border.thickness));
                window.draw(line);
            }
            if (border.down) {
                line.setPosition(absolute.position.x, absolute.position.y + absolute.size.h);
                line.setSize(sf::Vector2f(absolute.size.w, border.thickness));
                window.draw(line);
            }
            if (border.left) {
                line.setPosition(absolute.position.x - border.thickness, absolute.position.y);
                line.setSize(sf::Vector2f(border.thickness, absolute.size.h));
                window.draw(line);
            }
            if (border.right) {
                line.setPosition(absolute.position.x + absolute.size.w, absolute.position.y);
                line.setSize(sf::Vector2f(border.thickness, absolute.size.h));
                window.draw(line);
            }
        }
    }

    void Border::init() {
        __init();
        addReaction<RenderLayer>([this](futils::IMediatorPacket &pkg){
            auto &packet = futils::Mediator::rebuild<RenderLayer>(pkg);
            for (auto &obj: packet.objects)
            {
                if (!obj->has<components::Border>())
                    continue ;
                auto &border = obj->get<components::Border>();
                if (border.visible) {
                    renderBorder(border, *packet.window);
                }
            }
        });
        phase = Run;
    }

    void Border::run(float) {
        switch (phase)
        {
            case Init: return init();
            case Run: return ;
        }
    }
}