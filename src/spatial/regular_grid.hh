// Copyright MakeShape. 2019, All rights reserved.

#include <Eigen/Dense>

#pragma once

namespace makeshape {
namespace spatial {

class TriMesh;

class RegularGrid {
  public:
    RegularGrid(const Eigen::Vector3i size);
    bool build_binary_field(const TriMesh &m);
    bool build_distance_field(const TriMesh &m);
  private:
    const Eigen::Vector3i size_;
}; // RegularGrid

} // spatial 
} // makeshape
