//
// Created by Саша on 09.06.2026.
//

#include "../include/light.h"
namespace engine {
    Light::Light() {
        this->position = simpleStruct::Point({100,100,100});
    }
    Light::Light(simpleStruct::Point position) {
        this->position = position;
    }
    Light::Light(simpleStruct::Point position, float intensity) {
        this->position = position;
        this->intensity = intensity;
    }

    void Light::setPositon(simpleStruct::Point position) {
        //mb add check on verity position
        this->position = position;
    }
    void Light::setIntensity(float intensity) {
        this->intensity = intensity;
    }
}