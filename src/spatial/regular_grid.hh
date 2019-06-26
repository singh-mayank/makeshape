// Copyright MakeShape. 2019, All rights reserved.
#include "edges.hh"
#include "aabb.hh"
#include <Eigen/Dense>
#include <vector>

#pragma once

namespace makeshape {
namespace spatial {

class RegularGrid {
  public:
    RegularGrid(const size_t max_depth);
    bool build();

    //TODO(mayank): 
    // - build edges for visualization
    // - distance field for a mesh
    // - inside/outside field for a mesh
    // - 
  private:
    const size_t max_depth_;
}; // RegularGrid

} // spatial 
} // makeshape
