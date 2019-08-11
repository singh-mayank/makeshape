// Copyright MakeShape. 2019, All rights reserved.

#pragma once

#include <Eigen/Dense>


namespace makeshape {
namespace spatial {

struct Plane {
    Eigen::Vector3d origin;
    Eigen::Vector3d normal;     // expects normalized
};

} // spatial 
} // makeshape
