// Copyright MakeShape. 2019, All rights reserved.

#include <Eigen/Dense>

#pragma once

namespace makeshape {
namespace spatial {

struct Plane {
    Eigen::Vector3d origin;
    Eigen::Vector3d normal;     // expects normalized
};

} // spatial 
} // makeshape
