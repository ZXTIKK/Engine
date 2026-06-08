//
// Created by Саша on 08.06.2026.
//
#include "../include/camera.h"

//make field
#ifndef SENSITIVITY_CAMERA
#define SENSITIVITY_CAMERA 1
#endif
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
        this->position -= vecRotated*this->speed;
    }
    void Camera::goRight() {
        auto vec = this->viewVector;
        vec.y=0;
        vec = LinMath::normolise(vec);
        auto vecRotated = simpleStruct::Vector({vec.z, vec.y, -vec.x});
        this->position += vecRotated*this->speed;
    }
    void Camera::goUp() {
        this->position = simpleStruct::Point{this->position.x, this->position.y + this->speed, this->position.z};
    }
    void Camera::goDown() {
        this->position = simpleStruct::Point{this->position.x, this->position.y - this->speed, this->position.z};
    }

    void Camera::rotateHorizontal(int moveX) {
        float rad = LinMath::conversionToRadian(moveX);

        this->viewVector = LinMath::rotationVecY(
            LinMath::normolise(this->viewVector),
            rad
        );
    }

    void Camera::rotateVertical(int moveY) {
        float rad = LinMath::conversionToRadian(moveY);
        simpleStruct::Vector forward = LinMath::normolise(this->viewVector);
        simpleStruct::Vector right = LinMath::vecProd(forward, simpleStruct::Vector({0, 1, 0}));
        right = LinMath::normolise(right);
        this->viewVector = LinMath::rotateAroundAxis(forward, right, rad);
    }

    simpleStruct::Vector Camera::getViewVector() {
        return this->viewVector;
    }
    simpleStruct::Point Camera::getPosition() {
        return this->position;
    }
}