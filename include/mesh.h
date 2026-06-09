//
// Created by Саша on 07.06.2026.
//

#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H

#include <vector>
#include "linMath.h"
#include "simpleStruct.h"

namespace engine {
  class Mesh {
  private:
    std::vector<simpleStruct::Poligon> polygons;
    float farthestPoint;
    simpleStruct::Point centerMass;
    long mass;  //kg

    void calculateFarthestPoint();
    void calculateCenterMass();

  public:
    Mesh(std::vector<simpleStruct::Poligon> polygons);
    ~Mesh() = default;

    std::vector<simpleStruct::Poligon> getPolygons() const {
      return polygons;
    }

    static Mesh getCube();
  };
}
#endif //ENGINE_MESH_H
