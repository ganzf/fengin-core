//
// Created by clara on 1/11/18.
//

#include <Components/Editable.hpp>
#include "Text.hpp"
#include "Components/AbsoluteTransform.hpp"
#include "Camera.hpp"
#include "AssetLoader.hpp"

namespace
{
    std::unordered_map<futils::TextModifier, sf::Text::Style> textModifierToSfStyle = {
            {futils::TextModifier::None, sf::Text::Style::Regular},
            {futils::TextModifier::Italic, sf::Text::Style::Italic},
            {futils::TextModifier::Bold, sf::Text::Style::Bold},
            {futils::TextModifier::StrikeThrough, sf::Text::Style::StrikeThrough},
            {futils::TextModifier::Underline, sf::Text::Style::Underlined}
    };
}

namespace fender::systems::SFMLSystems
{
    void Text::renderText(components::Text const &txt, sf::RenderWindow &window)
    {
        auto &absolute = txt.getEntity().get<components::AbsoluteTransform>();
        if (absolute.size.w == 0 || absolute.size.h == 0)
            return ;
        sf::Text text;
        sf::Color color;

        color << txt.style.color;
        text.setFont((*_fonts)[txt.style.font]);
        text.setStyle(textModifierToSfStyle[txt.style.mod]);
        if (txt.getEntity().has<components::Editable>())
        {
            auto &edit = txt.getEntity().get<components::Editable>();
            if (edit.hasFocus)
                text.setString(txt.str + "|");
            else
                text.setString(txt.str);
        } else
            text.setString(txt.str);
        //std::cout << 0.25 *absolute.size.h << "compare to " << txt.style.size << std::endl;
        text.setCharacterSize(txt.style.size);

        if (text.getGlobalBounds().width > absolute.size.x)
            text.setCharacterSize((absolute.size.h / absolute.size.w) / absolute.size.w);

        text.setFillColor(color);
        float w_pos = absolute.position.x;
        if (txt.style.align == futils::Align::Center) {
            w_pos = absolute.position.x + absolute.size.w / 2 - text.getGlobalBounds().width / 2;
        } else if (txt.style.align == futils::Align::Right) {
            w_pos = absolute.position.w + absolute.size.w - text.getGlobalBounds().width;
        }
        float h_pos = absolute.position.y;
        if (txt.style.valign == futils::VAlign::Middle)
            h_pos = absolute.position.y + absolute.size.h / 2 - text.getGlobalBounds().height / 2;
        else if (txt.style.valign == futils::VAlign::Bottom)
            h_pos = absolute.position.y + absolute.size.h - text.getGlobalBounds().height / 2;
        text.setPosition(w_pos, h_pos);
        window.draw(text);
    }

    void Text::init() {
        __init();
        addReaction<RenderLayer>([this](futils::IMediatorPacket &pkg){
            if (_fonts == nullptr)
                return;
            auto &packet = futils::Mediator::rebuild<RenderLayer>(pkg);
            for (auto &obj: packet.objects)
            {
                if (!obj->has<components::Text>())
                    continue ;
                auto &text = obj->get<components::Text>();
                renderText(text, *packet.window);
            }
        });

        addReaction<AssetsLoaded>([this](futils::IMediatorPacket &pkg){
            auto &packet = futils::Mediator::rebuild<AssetsLoaded>(pkg);
            _fonts = packet.fonts;
        });

        events->send<RequestAssets>(RequestAssets());

        phase = Run;
    }

    void Text::run(float) {
        switch (phase)
        {
            case Init: return init();
            case Run: return ;
        }
    }
}
