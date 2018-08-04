//
// Created by arroganz on 1/3/18.
//


#pragma once

#include <Components/AbsoluteTransform.hpp>
#include <Components/Border.hpp>
#include <Components/ChildInfo.hpp>
# include "fender.hpp"
# include "Components/GameObject.hpp"
# include "Components/Transform.hpp"

namespace fender::entities {
    class GameObject : public futils::IEntity {

    public:
        GameObject() {
            attach<components::GameObject>();
            auto &transform = attach<components::Transform>();
            transform.position.z = 1;
            attach<components::AbsoluteTransform>();
            auto &border = attach<components::Border>();
            border.color = futils::Indianred;
            border.thickness = 2;
            border.visible = true;
        }

        ~GameObject() override {
            detach<components::GameObject>();
            detach<components::Transform>();
            detach<components::AbsoluteTransform>();
            detach<components::Border>();
            if (has<components::ChildInfo>()) {
                detach<components::ChildInfo>();
                std::cout << "Detached childinfo from " << this->getId() << std::endl;
            }
        }

        void setSize(float width, float height) {
            auto &transform = get<components::Transform>();
            transform.size.w = width;
            transform.size.h = height;
        }

        void setSize(futils::Vec2<float> const &size) {
            auto &transform = get<components::Transform>();
            transform.size.w = size.w;
            transform.size.h = size.h;
        }

        futils::Vec2<float> const &getSize() const {
            auto &transform = get<components::Transform>();
            return (transform.size);
        }

        int getWidth() const {
            auto &transform = get<components::Transform>();
            return (transform.size.w);
        }

        int getHeight() const {
            auto &transform = get<components::Transform>();
            return (transform.size.h);
        }

        void setPosition(float x, float y) {
            auto &transform = get<components::Transform>();
            transform.position.x = x;
            transform.position.y = y;
        }


        void setPosition(futils::Vec2<float> const &pos) {
            auto &transform = get<components::Transform>();
            transform.position.x = pos.x;
            transform.position.y = pos.y;
        }

        void setPosition(float x, float y, float z) {
            auto &transform = get<components::Transform>();
            transform.position.x = x;
            transform.position.y = y;
            transform.position.z = z;
        }

        Position const &getPosition() const {
            auto &transform = get<components::Transform>();
            return (transform.position);
        }

        int getPositionX() const {
            auto &transform = get<components::Transform>();
            return (transform.position.x);
        }

        int getPositionY() const {
            auto &transform = get<components::Transform>();
            return (transform.position.y);
        }

        int getPositionZ() const {
            auto &transform = get<components::Transform>();
            return (transform.position.z);
        }


        void setBorderVisible(bool visible) {
            auto &border = get<components::Border>();
            border.visible = visible;
        }

        void hide() {
            auto &object = get<components::GameObject>();
            object.hide();
        }

        void show() {
            auto &object = get<components::GameObject>();
            object.show();
        }

        void borderColor(futils::Color c) {
            auto &border = get<components::Border>();
            border.color = c;
        }

    };
}

