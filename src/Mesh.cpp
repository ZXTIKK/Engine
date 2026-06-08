//
// Created by Саша on 08.06.2026.
//
#include "../include/mesh.h"
namespace engine {
    Mesh::Mesh(std::vector<simpleStruct::Poligon> polygons) {
        this->polygons = polygons;
        calculateCenterMass();
        calculateFarthestPoint();
    }

    Mesh::~Mesh(){}

    void Mesh::calculateFarthestPoint() {
        this->farthestPoint = 0;
    }

    void Mesh::calculateCenterMass() {
        float xCenterMass{}, yCenterMass{}, zCenterMass{};
        for (simpleStruct::Poligon p : this->polygons) {
            xCenterMass += p.point1.x + p.point2.x + p.point3.x;
            yCenterMass += p.point1.y + p.point2.y + p.point3.y;
            zCenterMass += p.point1.z + p.point2.z + p.point3.z;
        }
        this->centerMass = simpleStruct::Point{xCenterMass, yCenterMass, zCenterMass};
    }
}