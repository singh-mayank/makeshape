// Copyright MakeShape. 2019, All rights reserved.

#pragma once

#include <Eigen/Dense>

namespace makeshape {
namespace spatial {

class SDF final {
  public:
    SDF(const int resolution, const Eigen::MatrixXd &pts);
    ~SDF() = default;

  private:
    const int resolution_;
    Eigen::MatrixXd sdf_;

}; // OctreeNode


} // spatial 
} // makeshape
