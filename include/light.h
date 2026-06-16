//
// Created by Саша on 08.06.2026.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H

#include "simpleStruct.h"

namespace engine {
    class Light {
    private:
        simpleStruct::Point position;
        float intensity;
    public:
        Light();
        Light(simpleStruct::Point position);
        Light(simpleStruct::Point position, float intensity);
        ~Light() = default;

        simpleStruct::Point getPosition() { return this->position; }
        float getIntensity() { return this->intensity; }

        void setPositon(simpleStruct::Point position);
        void setIntensity(float intensity);

    };
}
#endif //ENGINE_LIGHT_H
