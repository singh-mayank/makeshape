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

} // spatial 
} // makeshape
