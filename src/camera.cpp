//
// Created by Саша on 08.06.2026.
//
#include "../include/camera.h"

#include <iostream>
//make in field
#ifndef SENSITIVITY_CAMERA
#define SENSITIVITY_CAMERA 0.05
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
        this->position -= this->rightVec*this->speed;
    }

    void Camera::goRight() {
        this->position += this->rightVec*this->speed;
    }

    void Camera::goUp() {
        this->position = simpleStruct::Point{this->position.x, this->position.y + this->speed, this->position.z};
    }

    void Camera::goDown() {
        this->position = simpleStruct::Point{this->position.x, this->position.y - this->speed, this->position.z};
    }

    void Camera::findUpAndRightVec() {
        this->rightVec.x = -this->viewVector.z;
        this->rightVec.z = this->viewVector.x;
        this->rightVec = LinMath::normolise(this->rightVec);
        this->upVec = LinMath::vecProd(this->rightVec, this->viewVector);
        this->upVec = LinMath::normolise(this->upVec);
    }

    void Camera::rotateHorizontal(int moveX) {
        float rad = LinMath::conversionToRadian(moveX * SENSITIVITY_CAMERA);

        this->viewVector = LinMath::rotationVecY(
            LinMath::normolise(this->viewVector),
            rad
        );
        this->findUpAndRightVec();
    }

    void Camera::rotateVertical(int moveY) {
        if (LinMath::dot(this->viewVector,simpleStruct::Vector{0,1,0}) >= 0.99f || LinMath::dot(this->viewVector,simpleStruct::Vector{0,-1,0}) >= 0.99f) {
            this->viewVector = simpleStruct::Vector{1,0,0};
            return;
        }
        float rad = LinMath::conversionToRadian(moveY * SENSITIVITY_CAMERA);

        simpleStruct::Vector forward = LinMath::normolise(this->viewVector);

        simpleStruct::Vector worldUp = {0.0f, 1.0f, 0.0f};
        simpleStruct::Vector right;
        if (std::abs(LinMath::dot(forward, worldUp)) >= 0.99f) {
            right = LinMath::normolise(LinMath::vecProd(forward, {0.0f, 0.0f, 1.0f}));
        } else {
            right = LinMath::normolise(LinMath::vecProd(forward, worldUp));
        }

        this->viewVector = LinMath::rotateAroundAxis(forward, right, -rad);
        this->viewVector = LinMath::normolise(this->viewVector);
        this->findUpAndRightVec();
    }

    simpleStruct::Vector Camera::getViewVector() {
        return this->viewVector;
    }

    simpleStruct::Point Camera::getPosition() {
        return this->position;
    }

    float Camera::getFOV() {
        return this->fov;
    }

    void Camera::setFOV(float fov) {
        this->fov = fov;
    }


}