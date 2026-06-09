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
}