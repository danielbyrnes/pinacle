#pragma once

#include <vector>
#include <array>
#include <iostream>

namespace geometry {
struct Point3D {
    Point3D(double _x, double _y, double _z) : x(_x),y(_y), z(_z) {}
    Point3D() : x(0.),y(0.),z(0.) {}
    double x;
    double y;
    double z;

    double& operator[](int index) {
        if (index < 0 || index > 2) {
            throw std::out_of_range("index out of range");
        }
        if (index == 0) {
            return x;
        } else if (index == 1) {
            return y;
        } 
        return z;
    }

    double norm2() {
        return std::sqrt(x*x + y*y + z*z);
    }

    friend Point3D operator-(const Point3D& a, const Point3D& b) {
        return Point3D(a.x-b.x, a.y-b.y, a.z-b.z);
    }

    friend std::ostream& operator<<(std::ostream& os, const Point3D& p) {
        os << "(" << p.x << "," << p.y << "," << p.z << ")";
        return os;
    }
};
}