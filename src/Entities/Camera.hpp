//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "fender.hpp"
# include "GameObject.hpp"
# include "Components/Camera.hpp"
# include "Components/Children.hpp"

namespace fender::entities {
    class Camera : public GameObject {
    public:
        Camera() {
            auto &transform = get<components::Transform>();
            transform.position.z = 10;
            attach<components::Camera>();
            attach<components::Children>();
        }

        Camera(fender::entities::Window *win, std::string const &name = "Default") {
            auto &transform = get<components::Transform>();
            transform.position.z = 10;
            auto &cam = attach<components::Camera>();
            attach<components::Children>();
            cam.window = win;
            cam.name = name;
        }

        ~Camera() {
            detach<components::Camera>();
            detach<components::Children>();
            if (has<components::ChildInfo>()) {
                std::cout << "Detached childInfo from camera" << std::endl;
                detach<components::ChildInfo>();
            }
        }

        void setActivated(bool activated) {
            auto &cam = get<components::Camera>();
            cam.activated = activated;
        }

        void setWindow(fender::entities::Window *win) {
            auto &cam = get<components::Camera>();
            cam.window = win;
        }

        void setName(std::string const &name) {
            auto &cam = get<components::Camera>();
            cam.name = name;
        }

    };
}


