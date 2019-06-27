// Copyright MakeShape. 2019, All rights reserved.

#include <Eigen/Dense>

#pragma once

namespace makeshape {
namespace spatial {

struct Ray {
    Eigen::Vector3d origin;
    Eigen::Vector3d dir;
};

} // spatial 
} // makeshape
