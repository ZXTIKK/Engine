//
// Created by Саша on 08.06.2026.
//

#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include "linMath.h"
#include "simpleStruct.h"
#include <iostream>

namespace engine {
    class Camera {
    private:
        float speed;
        simpleStruct::Point position;
        simpleStruct::Vector viewVector;  //this can all times normalize
        // this fields for optimization
        simpleStruct::Vector upVec;
        simpleStruct::Vector rightVec{0,0,0};

        void findUpAndRightVec();

        int fov;
        //add in next time scene for multicamera and change camera, mb lock and modes

        float focus;


    public:
        Camera() {
            this->position = simpleStruct::Point({0,0,0});
            this->viewVector = simpleStruct::Vector({1,0,0});
            this->speed = 1;
            this->fov = 100;
            findUpAndRightVec();
        }
        Camera(simpleStruct::Point position, simpleStruct::Vector viewVector, float speed, int fov) {
            this->fov = fov;
            this->position = position;
            this->viewVector = LinMath::normolise(viewVector);
            this->speed = speed;
            findUpAndRightVec();
        }
        Camera(simpleStruct::Point position, simpleStruct::Vector viewVector, float speed) {
            this->fov = 100;
            this->position = position;
            this->viewVector = LinMath::normolise(viewVector);
            this->speed = speed;
            findUpAndRightVec();
        }
        Camera(simpleStruct::Point position) {
            this->position = position;
            this->viewVector = simpleStruct::Vector({1,0,0});
            this->speed = 1;
            this->fov = 100;
            findUpAndRightVec();
        }
        Camera(simpleStruct::Vector viewVector) {
            this->viewVector = LinMath::normolise(viewVector);
            this->speed = 1;
            this->position = simpleStruct::Point({0,0,0});
            this->fov = 100;
            findUpAndRightVec();
        }
        Camera(simpleStruct::Vector viewVector, simpleStruct::Point position) {
            this->viewVector = viewVector;
            this->position = position;
            this->fov = 100;
            this->speed = 1;
            findUpAndRightVec();
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
        simpleStruct::Vector getUpVec() {return this->upVec;}
        simpleStruct::Vector getRightVec() {return this->rightVec;}


    };
    inline std::ostream& operator << (std::ostream& os, Camera& cam) {
        os << "CAMERA POSITION\n[\n\t" <<
            "x: " << cam.getPosition().x << "\n\t"
            << "y: " << cam.getPosition().y << "\n\t"
            << "z: " << cam.getPosition().z << "\n]\n\n"
            << "CAMERA VIEW_VECTOR\n[\n\t"
            << "x: " << cam.getViewVector().x << "\n\t"
            << "y: " << cam.getViewVector().y << "\n\t"
            << "z: " << cam.getViewVector().z << "\n]\n";

        return os;
    }
}
#endif //ENGINE_CAMERA_H
