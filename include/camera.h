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
        simpleStruct::Vector viewVector; //this can all times normalize
        //add in next time scene for multicamera and change camera, mb lock and mode
    public:
        Camera() {
            this->position = simpleStruct::Point({0,0,0});
            this->viewVector = simpleStruct::Vector({1,0,0});
            this->speed = 1;
        }
        Camera(simpleStruct::Point position, simpleStruct::Vector viewVector, float speed) {

            this->position = position;
            this->viewVector = LinMath::normolise(viewVector);
            this->speed = speed;
        }
        Camera(simpleStruct::Point position) {
            this->position = position;
            this->viewVector = simpleStruct::Vector({1,0,0});
            this->speed = 1;
        }
        Camera(simpleStruct::Vector viewVector) {
            this->viewVector = LinMath::normolise(viewVector);
            this->speed = 1;
            this->position = simpleStruct::Point({0,0,0});
        }
        ~Camera() {}

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

    };
}
#endif //ENGINE_CAMERA_H
