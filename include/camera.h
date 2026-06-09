//
// Created by Саша on 08.06.2026.
//

#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include "linMath.h"
#include "simpleStruct.h"

namespace engine {
    class Camera {
    private:
        float speed;
        simpleStruct::Point position;
        simpleStruct::Vector viewVector;  //this can all times normalize
        int fov;
        //add in next time scene for multicamera and change camera, mb lock and modes
    public:
        Camera() {
            this->position = simpleStruct::Point({0,0,0});
            this->viewVector = simpleStruct::Vector({1,0,0});
            this->speed = 1;
            this->fov = 100;
        }
        Camera(simpleStruct::Point position, simpleStruct::Vector viewVector, float speed, int fov) {
            this->fov = fov;
            this->position = position;
            this->viewVector = LinMath::normolise(viewVector);
            this->speed = speed;
        }
        Camera(simpleStruct::Point position, simpleStruct::Vector viewVector, float speed) {
            this->fov = 100;
            this->position = position;
            this->viewVector = LinMath::normolise(viewVector);
            this->speed = speed;
        }
        Camera(simpleStruct::Point position) {
            this->position = position;
            this->viewVector = simpleStruct::Vector({1,0,0});
            this->speed = 1;
            this->fov = 100;
        }
        Camera(simpleStruct::Vector viewVector) {
            this->viewVector = LinMath::normolise(viewVector);
            this->speed = 1;
            this->position = simpleStruct::Point({0,0,0});
            this->fov = 100;
        }
        Camera(simpleStruct::Vector viewVector, simpleStruct::Point position) {
            this->viewVector = viewVector;
            this->position = position;
            this->fov = 100;
            this->speed = 1;
        }
        ~Camera() = default;

        // movement
        void goForward();
        void goBack();
        void goLeft();
        void goRight();
        void goUp();
        void goDown();

        // rotation
        void rotateHorizontal(int moveX);
        void rotateVertical(int moveY);

        simpleStruct::Vector getViewVector();
        simpleStruct::Point getPosition();
        float getFOV();

        void setFOV(float fov);
    };
}
#endif //ENGINE_CAMERA_H
