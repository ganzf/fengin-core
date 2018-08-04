//
// Created by arroganz on 1/15/18.
//


#pragma once

#include <Components/World.hpp>
#include <Components/Color.hpp>
#include <Components/ViewInfo.hpp>
# include "fender.hpp"
# include "ListView.hpp"
# include "Text.hpp"
# include "Button.hpp"
#include "Image.hpp"

namespace fender::entities {
    class TextBox : public ListView {
        ListView *_scroll{nullptr};
        ListView *_stream{nullptr};
        Button *_Up{nullptr};
        Button *_Down{nullptr};
        int size;
        std::string buffer;
        int fontSize{12};

        void initScroll()
        {
            _list->order = futils::Ordering::Horizontal;
            _list->padding = 0.2;
            _scroll = &entityManager->create<ListView>();
            _list->content.push_back(_scroll);
            auto &scrollBorder = _scroll->get<components::Border>();
            scrollBorder.visible = false;
            auto &scrollView = _scroll->get<components::ListView>();
            scrollView.name = "ScrollView";
            _Up = &entityManager->create<Button>();
            _Up->setBorderVisible(false);
            auto &upImage = _Up->get<components::Image>();
            upImage.file = "uptextbox.png";
            auto &upSize = _Up->get<components::Transform>();
            upSize.size.w = 0.5;
            upSize.size.h = 0.5;
            auto &upAction = _Up->get<components::Clickable>();
            upAction.func = [this](){
                auto &stream = _stream->get<components::ListView>();
                if (stream.offset > 0)
                    stream.offset--;
            };
            _Down = &entityManager->create<Button>();
            _Down->setBorderVisible(false);
            auto &downImage = _Down->get<components::Image>();
            downImage.file = "downtextbox.png";
            auto &downSize = _Down->get<components::Transform>();
            downSize.size.w = 0.5;
            downSize.size.h = 0.5;
            auto &downAction = _Down->get<components::Clickable>();
            downAction.func = [this](){
                auto &stream = _stream->get<components::ListView>();
                if (stream.offset + stream.size < (int)stream.content.size())
                    stream.offset++;
            };
            scrollView.content.push_back(_Up);
            scrollView.content.push_back(_Down);
            scrollView.fit = true;

            auto &scrollInfo = _scroll->attach<components::ViewInfo>();
            scrollInfo.w = 5;
            scrollInfo.h = 100;

            _scroll->setBorderVisible(true);
            _scroll->borderColor(futils::Darkorange);
        }
        void initStream(int size)
        {
            static int i = 0;
            i++;
            _stream = &entityManager->create<ListView>(size);
            auto &streamBorder = _stream->get<components::Border>();
            streamBorder.visible = false;
            _stream->setBorderVisible(true);
            _stream->borderColor(futils::Sandybrown);
            auto &list = _stream->get<components::ListView>();
            list.name = "TextBoxTextStream" + std::to_string(i);
            list.order = futils::Ordering::Vertical;
            _list->content.push_back(_stream);
            list.fit = true;

            auto &view = _stream->attach<components::ViewInfo>();
            view.w = 100;
            if (_scroll)
                view.w -= _scroll->get<components::ViewInfo>().w;
        }
    public:
        explicit TextBox(int size = 1, bool scrollable = false): size(size)
        {
            afterBuild = [this, size, scrollable](){
                _list->name = "TextBoxContainer" + std::to_string(size);
                if (scrollable) {
                    initScroll();
                    initStream(size);
                } else {
                    initStream(size);
                }
            };
        }
        ~TextBox()
        {
            if (_scroll != nullptr)
            {
                entityManager->destroy(*_scroll);
                entityManager->destroy(*_Up);
                entityManager->destroy(*_Down);
            }
            entityManager->destroy(*_stream);
        }

        TextBox &operator << (int size)
        {
            fontSize = size;
            return *this;
        }
        TextBox &operator << (std::string const &str)
        {
            if (!_stream)
                return *this;
            if (str == futils::endl) {
                auto &list = _stream->get<components::ListView>();
                auto txt = &entityManager->create<Text>(buffer);
                auto &font = txt->get<components::Text>();
                font.style.size = fontSize;
                font.style.font = "arial.ttf";
                auto &border = txt->get<components::Border>();
                border.visible = false;
                border.color = futils::Lightgoldenrodyellow;
                auto &tr = txt->get<components::Transform>();
                auto worlds = entityManager->get<components::World>();
                if (!worlds.empty())
                    tr.size.h = (float)font.style.size / (float)worlds.front()->unit;
                if (_scroll != nullptr) {
                    tr.size.w = this->get<components::Transform>().size.w - _scroll->get<components::Transform>().size.w;
                } else {
                    tr.size.w = _stream->get<components::Transform>().size.w;
                }
                if ((int)list.content.size() + 1 > list.size) {
                    list.offset++;
                }

                list.content.push_back(txt);
                buffer = "";
            } else {
                buffer += str;
            }
            return *this;
        }
        TextBox &operator << (Text &txt) {

            auto &list = _stream->get<components::ListView>();
            auto &tr = txt.get<components::Transform>();
            auto &txtInfo = txt.get<components::Text>();
            auto worlds = entityManager->get<components::World>();
            if (!worlds.empty())
                tr.size.h = txtInfo.style.size / worlds.front()->unit;
            if (_scroll != nullptr) {
                tr.size.w = this->get<components::Transform>().size.w - _scroll->get<components::Transform>().size.w;
            } else {
                tr.size.w = _stream->get<components::Transform>().size.w;
            }
            if ((int)list.content.size() + 1 > list.size) {
                list.offset++;
            }
            list.content.push_back(&txt);
            return *this;
        }
    };
}
