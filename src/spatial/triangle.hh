// Copyright MakeShape. 2019, All rights reserved.

#include <Eigen/Dense>

#pragma once

namespace makeshape {
namespace spatial {

struct Triangle {
    Eigen::Vector3d v0;
    Eigen::Vector3d v1;
    Eigen::Vector3d v2;
};

Eigen::Vector3d normal(const Triangle &t) {
   return ((t.v1 - t.v0).cross((t.v2 - t.v0))).normalized();
}

double area(const Triangle &t) {
    // determinant of 3x3 matrix
    return 0.0;
}



} // spatial 
} // makeshape
