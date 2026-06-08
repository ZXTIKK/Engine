//
// Created by Саша on 07.06.2026.
//
#include <complex>
#include <vector>
#include <cmath>

#include "simpleStruct.h"

#ifndef ENGINE_LINMATH_H
#define ENGINE_LINMATH_H
namespace LinMath {
    /*
     * use point 2 when center
     */
    inline simpleStruct::Vector vecProd(simpleStruct::Vector vec1, simpleStruct::Vector vec2) {
        /*
         |   i     j      k   |  culc vec
         |vec1.x vec1.y vec1.z|  vec1
         |vec2.x vec2.y vec2.z|  vec2
         */
        return simpleStruct::Vector({
            vec1.y*vec2.z - vec1.z*vec2.y,
            vec1.x*vec2.z - vec1.z*vec2.x,
            vec1.x*vec2.y - vec1.y*vec2.x
        });
    }
    inline simpleStruct::Vector vecProd(simpleStruct::Point p1, simpleStruct::Point p2, simpleStruct::Point p3) {
        simpleStruct::Vector v1{p1.x - p2.x, p1.y - p2.y, p1.z - p2.z};
        simpleStruct::Vector v2{p3.x - p2.x, p3.y - p2.y, p3.z - p2.z};
        return vecProd(v1, v2);
    }
    inline float lenVec(simpleStruct::Vector vec) {
        return std::sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z); // optimize this in nex time sqrt high cost
    }
    inline simpleStruct::Vector normolise(simpleStruct::Vector vec) {
        float lV = lenVec(vec);
        if (lV < 1e-6f) {
            return simpleStruct::Vector({0.0f, 0.0f, 0.0f});
        }
        float invLv = 1.0f / lV;
        return simpleStruct::Vector({
            vec.x * invLv,
            vec.y * invLv,
            vec.z * invLv
        });
    }
    inline float scalarProd(simpleStruct::Vector vec1, simpleStruct::Vector vec2) {
        if (lenVec(vec1) != 1 || lenVec(vec2) != 1) {
            vec1 = normolise(vec1);
            vec2 = normolise(vec2);
        }
        return vec1*vec2;
    }
    inline void culcNormal(simpleStruct::Poligon& pol) {
        pol.normal = LinMath::normolise(LinMath::vecProd(pol.point1, pol.point2, pol.point3));
    }
    inline simpleStruct::Vector rotationVecX(const simpleStruct::Vector& vec1, float radians) {
        float cosA = std::cos(radians);
        float sinA = std::sin(radians);

        return LinMath::normolise(simpleStruct::Vector({
            vec1.x,
            vec1.y * cosA - vec1.z * sinA,
            vec1.y * sinA + vec1.z * cosA
        }));
    }

    // Поворот вокруг оси Y (изменяются только X и Z)
    inline simpleStruct::Vector rotationVecY(const simpleStruct::Vector& vec1, float radians) {
        float cosA = std::cos(radians);
        float sinA = std::sin(radians);

        return LinMath::normolise(simpleStruct::Vector({
            vec1.x * cosA + vec1.z * sinA,
            vec1.y,
            -vec1.x * sinA + vec1.z * cosA
        }));
    }

    inline simpleStruct::Vector rotationVecZ(const simpleStruct::Vector& vec1, float radians) {
        float cosA = std::cos(radians);
        float sinA = std::sin(radians);

        return LinMath::normolise(simpleStruct::Vector({
            vec1.x * cosA - vec1.y * sinA,
            vec1.x * sinA + vec1.y * cosA,
            vec1.z
        }));
    }
    inline float conversionToRadian(float degrees) {
        return degrees * std::numbers::pi / 180.0f;
    }
    inline simpleStruct::Vector rotateAroundAxis(const simpleStruct::Vector& v, const simpleStruct::Vector& axis, float radians) {
        float cosA = std::cos(radians);
        float sinA = std::sin(radians);

        simpleStruct::Vector cross = vecProd(axis, v);

        float dot = scalarProd(axis, v);

        float resX = v.x * cosA + cross.x * sinA + axis.x * dot * (1.0f - cosA);
        float resY = v.y * cosA + cross.y * sinA + axis.y * dot * (1.0f - cosA);
        float resZ = v.z * cosA + cross.z * sinA + axis.z * dot * (1.0f - cosA);

        return simpleStruct::Vector({resX, resY, resZ});
    }
}
#endif //ENGINE_LINMATH_H
