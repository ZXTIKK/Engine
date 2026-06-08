//
// Created by Саша on 08.06.2026.
//
#include "../include/camera.h"

// Y - high

namespace engine {
    void Camera::goForward() {
        this->position += this->viewVector*this->speed;
    }
    void Camera::goBack() {
        this->position -= this->viewVector*this->speed;
    }
    void Camera::goLeft() {
        auto vec = this->viewVector;
        vec.y=0;
        vec = LinMath::normolise(vec);
        auto vecRotated = simpleStruct::Vector({vec.z, vec.y, -vec.x});
        this->position += vecRotated*this->speed;
    }
    void Camera::goRight() {
        auto vec = this->viewVector;
        vec.y=0;
        vec = LinMath::normolise(vec);
        auto vecRotated = simpleStruct::Vector({vec.z, vec.y, -vec.x});
        this->position -= vecRotated*this->speed;
    }
    void Camera::goUp() {
        this->position = simpleStruct::Point{this->position.x, this->position.y + this->speed, this->position.z};
    }
    void Camera::goDown() {
        this->position = simpleStruct::Point{this->position.x, this->position.y - this->speed, this->position.z};
    }

    void Camera::rotateHorizontal() {

    }
    void Camera::rotateVertical() {

    }

    simpleStruct::Vector Camera::getViewVector() {
        return this->viewVector;
    }
    simpleStruct::Point Camera::getPosition() {
        return this->position;
    }
}