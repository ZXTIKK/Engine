//
// Created by Саша on 07.06.2026.
//

#ifndef ENGINE_SIMPLESTRUCT_H
#define ENGINE_SIMPLESTRUCT_H

#include <concepts>
#include <iostream>
// #include "linMath.h"

/*
 * Remake all operator !!!
 */

namespace simpleStruct {
    template <typename T>
    concept arithmetic = std::integral<T> || std::floating_point<T>;

    union Color {
        unsigned int rgba;
        struct {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;
        };
    };

    struct Vector {
        float x;
        float y;
        float z;
        float operator*(const Vector& vector) const {
            return x * vector.x + y * vector.y + z * vector.z;
        }
        Vector operator+(const Vector& vector) {
            return Vector(x + vector.x, y + vector.y, z + vector.z);
        }
        Vector operator-(const Vector& vector) {
            return Vector(x - vector.x, y - vector.y, z - vector.z);
        }
        Vector operator+=(const Vector& vector) {
            x += vector.x;
            y += vector.y;
            z += vector.z;
            return Vector({x,y,z});
        }
        Vector operator-=(const Vector& vector) {
            x -= vector.x;
            y -= vector.y;
            z -= vector.z;
            return Vector({x,y,z});
        }

        template <arithmetic T>
        Vector operator+=(T& value) {
            x += value;
            y += value;
            z += value;
            return Vector({x,y,z});
        }
        template <arithmetic T>
        Vector operator*=(T& value) {
            x *= value;
            y *= value;
            z *= value;
            return Vector({x,y,z});
        }
        template <arithmetic T>
        Vector operator*(T& value) {
            return Vector({x*value,y*value,z*value});
        }

    };

    //this point for poligon
    struct Point {
        float x;
        float y;
        float z;
        Point operator+(const Point& vector) {
            return Point(x + vector.x, y + vector.y, z + vector.z);
        }
        Point operator-(const Point& vector) {
            return Point(x - vector.x, y - vector.y, z - vector.z);
        }
        Point operator+=(const Point& vector) {
            x += vector.x;
            y += vector.y;
            z += vector.z;
            return Point({x,y,z});
        }
        Point operator-=(const Point& vector) {
            x -= vector.x;
            y -= vector.y;
            z -= vector.z;
            return Point({x,y,z});
        }

        template <arithmetic T>
        Point operator+=(T& value) {
            x += value;
            y += value;
            z += value;
            return Point({x,y,z});
        }
        template <arithmetic T>
        Point operator*=(T& value) {
            x *= value;
            y *= value;
            z *= value;
            return Point({x,y,z});
        }
        template <arithmetic T>
        Point operator*(T& value) {
            return Point({x*value,y*value,z*value});
        }
        Point operator+=(const Vector& vector) {
            x+=vector.x;
            y+=vector.y;
            z+=vector.z;
            return Point({x,y,z});
        }
        Point operator-=(const Vector& vector) {
            x-=vector.x;
            y-=vector.y;
            z-=vector.z;
            return Point({x,y,z});
        }
        Point operator=(const Point& vector) {
            x=vector.x;
            y=vector.y;
            z=vector.z;
            return Point({x,y,z});
        }

        Point operator-( const Point p) const {
            return Point({x-p.x,y-p.y,z-p.z});
        }
    };

    struct Point2D {
        int x;
        int y;
        float z;

        Point2D operator+(const Point2D& point2d) {
            return Point2D(x + point2d.x, y + point2d.y,z);
        }
        Point2D operator-(const Point2D& point2d) {
            return Point2D(x - point2d.x, y - point2d.y,z);
        }
        Point2D operator+=(const Point2D& point2d) {
            x+=point2d.x;
            y+=point2d.y;
            return Point2D({x,y,z});
        }
        Point2D operator-=(const Point2D& point2d) {
            x-=point2d.x;
            y-=point2d.y;
            return Point2D({x,y,z});
        }
        template <arithmetic T>
        Point2D operator+=(T& value) {
            x+=value;
            y+=value;
            return Point2D({x,y,z});
        }
        template <arithmetic T>
        Point2D operator*=(T& value) {
            x*=value;
            y*=value;
            return Point2D({x,y,z});
        }
        template <arithmetic T>
        Point2D operator*(T& value) {
            return Point2D({x*value,y*value,z});
        }
    };

    //this poligon for visual
    struct Poligon {
        Point point1;
        Point point2;
        Point point3;
        Vector normal;
        Color color;
    };

    inline std::ostream& operator<<(std::ostream& os, const Poligon& pol) {
        os << "Poligon[\n"
           << "  p1: (" << pol.point1.x << ", " << pol.point1.y << ", " << pol.point1.z << ")\n"
           << "  p2: (" << pol.point2.x << ", " << pol.point2.y << ", " << pol.point2.z << ")\n"
           << "  p3: (" << pol.point3.x << ", " << pol.point3.y << ", " << pol.point3.z << ")\n"
           << "  normal: (" << pol.normal.x << ", " << pol.normal.y << ", " << pol.normal.z << ")\n"
           << "  color: RGBA(" << (int)pol.color.r << ", " << (int)pol.color.g << ", " << (int)pol.color.b << ", " << (int)pol.color.a << ")\n"
           << "]";
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const Vector& vec) {
        os << "Vector[\n"
           << "  x: (" << vec.x << ")\n"
           << "  y: (" <<  vec.y << ")\n"
           << "  z: (" << vec.z << ")\n"
           << "]";
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "Point[\n"
           << "  x: (" << point.x << ")\n"
           << "  y: (" <<  point.y << ")\n"
           << "  z: (" << point.z << ")\n"
           << "]";
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, Point2D& point) {
        os << "Vector[\n"
           << "  x: (" << point.x << ")\n"
           << "  y: (" <<  point.y << ")\n"
           << "]";
        return os;
    }

}


#endif //ENGINE_SIMPLESTRUCT_H
