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
    public:
        Light();
        Light(simpleStruct::Point position);
        ~Light() = default;
    };
}
#endif //ENGINE_LIGHT_H
