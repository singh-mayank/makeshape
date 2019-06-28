// Copyright MakeShape. 2019, All rights reserved.

#include <Eigen/Dense>

#pragma once

namespace makeshape {
namespace spatial {

struct Ray {
    Eigen::Vector3d origin;
    Eigen::Vector3d dir;    // expects normalized
};

struct BoundedRay {
    Ray r;
    double t;
};

BoundedRay make_bounded_ray(Eigen::Vector3d p1, Eigen::Vector3d p2) {
    Eigen::Vector3d dir = (p2 - p1);
    double t = dir.norm();
    Ray r{p1, dir.normalized()};
    return BoundedRay{r, t};
}

} // spatial 
} // makeshape
