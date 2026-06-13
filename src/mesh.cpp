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

    Mesh Mesh::getCube() {
        simpleStruct::Poligon zsn{
            simpleStruct::Point{0,0,0},
            simpleStruct::Point{0,15,0},
            simpleStruct::Point{0,0,15},
            simpleStruct::Vector{0,0,0},
            simpleStruct::Color{.r=255,.g=0,.b=0,.a=255}
        };
        simpleStruct::Poligon zsv{
            simpleStruct::Point{0,15,0},
            simpleStruct::Point{0,15,15},
            simpleStruct::Point{0,0,15},
            simpleStruct::Vector{0,0,0},
            simpleStruct::Color{.r=255,.g=0,.b=0,.a=255}
        };

        simpleStruct::Poligon psn{
            simpleStruct::Point{15,0,15},
            simpleStruct::Point{15,15,0},
            simpleStruct::Point{15,0,0},
            simpleStruct::Vector{0,0,0},
            simpleStruct::Color{.r=0,.g=255,.b=239,.a=255}
        };
        simpleStruct::Poligon psv{
            simpleStruct::Point{15,0,15},
            simpleStruct::Point{15,15,15},
            simpleStruct::Point{15,15,0},
            simpleStruct::Vector{0,0,0},
            simpleStruct::Color{.r=0,.g=255,.b=239,.a=255}
        };

        simpleStruct::Poligon vsn{
            simpleStruct::Point{15,0,0},
            simpleStruct::Point{15,0,15},
            simpleStruct::Point{0,0,0},
            simpleStruct::Vector{0,0,0},
            simpleStruct::Color{.r=0,.g=255,.b=0,.a=255}
        };
        simpleStruct::Poligon vsnn{
            simpleStruct::Point{15,0,15},
            simpleStruct::Point{0,0,15},
            simpleStruct::Point{0,0,0},
            simpleStruct::Vector{0,0,0},
            simpleStruct::Color{.r=0,.g=255,.b=0,.a=255}
        };

        simpleStruct::Poligon vsv{
            simpleStruct::Point{0,15,0},
            simpleStruct::Point{15,15,15},
            simpleStruct::Point{15,15,0},
            simpleStruct::Vector{0,0,0},
            simpleStruct::Color{.r=0,.g=0,.b=255,.a=255}
        };
        simpleStruct::Poligon vsvv{
            simpleStruct::Point{0,15,0},
            simpleStruct::Point{0,15,15},
            simpleStruct::Point{15,15,15},
            simpleStruct::Vector{0,0,0},
            simpleStruct::Color{.r=0,.g=0,.b=255,.a=255}
        };

        simpleStruct::Poligon rsv{
            simpleStruct::Point{0,0,0},
            simpleStruct::Point{15,15,0},
            simpleStruct::Point{0,15,0},
            simpleStruct::Vector{0,0,0},
            simpleStruct::Color{.r=200,.g=255,.b=0,.a=255}
        };
        simpleStruct::Poligon rsn{
            simpleStruct::Point{0,0,0},
            simpleStruct::Point{15,0,0},
            simpleStruct::Point{15,15,0},
            simpleStruct::Vector{0,0,0},
            simpleStruct::Color{.r=200,.g=255,.b=0,.a=255}
        };

        simpleStruct::Poligon lsv{
            simpleStruct::Point{0,15,15},
            simpleStruct::Point{15,15,15},
            simpleStruct::Point{0,0,15},
            simpleStruct::Vector{0,0,0},
            simpleStruct::Color{.r=255,.g=255,.b=255,.a=255}
        };
        simpleStruct::Poligon lsn{
            simpleStruct::Point{15,15,15},
            simpleStruct::Point{15,0,15},
            simpleStruct::Point{0,0,15},
            simpleStruct::Vector{0,0,0},
            simpleStruct::Color{.r=255,.g=255,.b=255,.a=255}
        };
        std::vector<simpleStruct::Poligon> vecPol{lsn,lsv,rsn,rsv,vsvv,vsv,vsnn,vsn,psv,zsn,zsv,psn};
        for (auto& p : vecPol) {
            LinMath::culcNormal(p);
        }
        return Mesh(vecPol);
    }
}